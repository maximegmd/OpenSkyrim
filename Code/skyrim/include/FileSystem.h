#pragma once

class BSArchive;
class FileSystem
{
public:

	FileSystem(const std::string& aRoot = "/");
	FileSystem(const FileSystem&) = delete;
	~FileSystem();

private:

	std::vector<std::unique_ptr<BSArchive>> m_archives;
};