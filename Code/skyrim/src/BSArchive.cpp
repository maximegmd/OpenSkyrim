#include "BSArchive.h"

BSArchive::BSArchive(const fs::path& aPath)
	: m_file(aPath.c_str(), std::ios::binary)
{
	assert(m_file.is_open());

	m_file.read((char*)&m_header, sizeof(m_header));
	assert(m_header.m_fileId == kFileId);
	assert(m_header.m_version == kVersion);

	m_file.seekg(m_header.m_offset + m_header.m_totalFolderNameLength + m_header.m_folderCount * 25 + 16 * m_header.m_fileCount, std::ios::beg);

	std::vector<std::string> fileNames(m_header.m_fileCount);
	for (auto i = 0; i < m_header.m_fileCount; ++i)
	{
		std::getline(m_file, fileNames[i], '\0');
	}

	m_file.seekg(m_header.m_offset, std::ios::beg);

	m_folderRecords.resize(m_header.m_folderCount);
	for (auto i = 0; i < m_header.m_folderCount; ++i)
	{
		m_file.read((char*)&m_folderRecords[i], 24);
	}

	for (auto i = 0; i < m_header.m_folderCount; ++i)
	{
		uint8_t length = 0;
		m_file.read((char*)&length, 1);
		std::string str(length, '\0');

		m_file.read(str.data(), length);
		m_folderRecords[i].m_name = str;

		for (auto j = 0; j < m_folderRecords[i].m_fileCount; ++j)
		{
			FileInfo f;
			m_file.read((char*)&f, 16);
			f.m_name = fileNames[j];
			cout << f.m_name << endl;
		}
	}

}

BSArchive::~BSArchive()
{

}