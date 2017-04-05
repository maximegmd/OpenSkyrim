#include "BSArchive.h"
#include "FileSystem.h"

FileSystem::FileSystem(const std::string& aRoot /* = "/" */)
{
	for (auto& p : fs::directory_iterator(aRoot))
	{
		if (p.path().has_extension() && p.path().extension() == ".bsa")
		{
			m_archives.push_back(std::make_unique<BSArchive>(p.path()));
		}
	}
}

FileSystem::~FileSystem()
{

}