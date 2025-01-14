#pragma once
#ifndef ES_APP_FILE_SORTS_H
#define ES_APP_FILE_SORTS_H

#include "FileData.h"
#include <vector>

namespace FileSorts
{
	bool compareName(const FileData* file1, const FileData* file2);
	bool compareFullSystem(const FileData* file1, const FileData* file2);
	bool comparePublisher(const FileData* file1, const FileData* file2);
	bool compareFirstRelease(const FileData* file1, const FileData* file2);
	bool compareGenre(const FileData* file1, const FileData* file2);
	bool compareNumPlayers(const FileData* file1, const FileData* file2);
	bool compareRegion(const FileData* file1, const FileData* file2);
	bool compareTimesPlayed(const FileData* file1, const FileData* file2);
	bool compareLastPlayed(const FileData* file1, const FileData* file2);

	void ignoreLeadingArticles(std::string &name1, std::string &name2);

	extern const std::vector<FileData::SortType> SortTypes;
};

#endif // ES_APP_FILE_SORTS_H
