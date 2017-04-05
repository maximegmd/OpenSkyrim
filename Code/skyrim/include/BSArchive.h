#pragma once

class BSArchive
{
public:

	enum
	{
		kFileId = 'ASB',
		kVersion = 0x69
	};

	BSArchive(const fs::path& aPath);
	BSArchive(const BSArchive&) = delete;
	~BSArchive();

private:

	struct Header
	{
		uint32_t m_fileId;
		uint32_t m_version;
		uint32_t m_offset;
		uint32_t m_archiveFlags;
		uint32_t m_folderCount;
		uint32_t m_fileCount;
		uint32_t m_totalFolderNameLength;
		uint32_t m_totalFileNameLength;
		uint32_t m_fileFlags;
	};

	struct FolderRecord
	{
		uint64_t m_nameHash;
		uint32_t m_fileCount;
		uint32_t m_unk1;
		uint64_t m_offset;

		std::string m_name;
	};

	struct FileInfo
	{
		uint64_t m_hash;
		uint32_t m_sizeFlags;
		uint32_t m_offset;

		std::string m_name;
	};

	std::ifstream m_file;
	Header m_header;
	std::vector<FolderRecord> m_folderRecords;
};