require("premake", ">=5.0.0-alpha10")

workspace ("OpenSkyrim")

    ------------------------------------------------------------------
    -- setup common settings
    ------------------------------------------------------------------
    configurations { "PriRel", "PubRel" }
    defines { "_CRT_SECURE_NO_WARNINGS", "_ELPP_NO_DEFAULT_LOG_FILE" }
    flags { "StaticRuntime" }
    floatingpoint ("Fast")
    location ("Projects")
    startproject ("Skyrim")
    vectorextensions ("SSE2")

    platforms { "x64" }

    includedirs
    { 
        "../Include/", 
        "../Code/",          
        "../Code/mhook/", 
        "../Code/log",
    }

    symbols ("On")
    
    filter { "action:vs*"}
        buildoptions { "/wd4512", "/wd4996", "/wd4018", "/Zm500", "/std:c++latest" }
        
    filter { "action:gmake" }
        buildoptions { "-g --std=c++17 -fpermissive" }
        linkoptions ("-lm -lpthread -pthread -Wl,--no-as-needed -lrt -g")

    filter { "configurations:PriRel" }
        optimize ("On")
        targetsuffix ("_r")
        
    filter { "configurations:PubRel" }
        defines { "NDEBUG" }
        optimize ("On")

        group ("Client")                        
            project ("Skyrim")
                kind ("ConsoleApp")
                language ("C++")
                pchheader ("stdafx.h")
                pchsource ("../Code/skyrim/src/stdafx.cpp")
                targetname ("TESV")

                defines
                {
                }

                includedirs 
                {
                    "../Code/skyrim/include/",
                }

                files 
                {
                    "../Code/skyrim/include/**.h",
                    "../Code/skyrim/src/**.cpp"
                }

                links 
                { 
                    "disasm",
                    "mhook",
                    "winmm",
                    "dbghelp",
                }

                forceincludes
                {
                    "stdafx.h"
                }

                targetdir ("bin")

                includedirs
                {
                    "../Include/DirectXTK"
                }

                libdirs 
                {
                    "lib"
                }

                links
                {
                    "d3d11.lib",
                    "DirectXTK.lib"
                }

        if (os.is("Windows") == true) then
            project ("disasm")
                kind ("StaticLib")
                language ("C")
                targetname ("disasm")

                includedirs
                { 
                    "../Code/disasm/" 
                }

                files
                {
                    "../Code/disasm/*.c" 
                }

                targetdir ("lib")

            project ("mhook")
                kind ("StaticLib")
                language ("C++")
                targetname ("mhook")

                includedirs
                {
                    "../Code/disasm/" 
                }
                
                files
                {
                    "../Code/mhook/*.cpp"
                }

                targetdir ("lib")
        end
