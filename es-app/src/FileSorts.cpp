#include "FileSorts.h"

#include "utils/StringUtil.h"
#include "Settings.h"
#include "Log.h"

namespace FileSorts
{

	const FileData::SortType typesArr[] = {
		FileData::SortType(&compareName, true, "name"),

		FileData::SortType(&compareFirstRelease, true, "first release date"),
	};

	const std::vector<FileData::SortType> SortTypes(typesArr, typesArr + sizeof(typesArr)/sizeof(typesArr[0]));

	//returns if file1 should come before file2
	bool compareName(const FileData* file1, const FileData* file2)
	{
		// we compare the actual metadata name, as collection files have the system appended which messes up the order
		std::string name1 = Utils::String::toUpper(file1->metadata.get("sortname"));
		std::string name2 = Utils::String::toUpper(file2->metadata.get("sortname"));
		if(name1.empty()){
			name1 = Utils::String::toUpper(file1->metadata.get("name"));
		}
		if(name2.empty()){
			name2 = Utils::String::toUpper(file2->metadata.get("name"));
		}

		ignoreLeadingArticles(name1, name2);

		return name1.compare(name2) < 0;
	}

	bool compareFirstRelease(const FileData* file1, const FileData* file2)
	{
		// since it's stored as an ISO string (YYYYMMDDTHHMMSS), we can compare as a string
		// as it's a lot faster than the time casts and then time comparisons
		return (file1)->metadata.get("firstrelease") < (file2)->metadata.get("firstrelease");
	}

	//If option is enabled, ignore leading articles by temporarily modifying the name prior to sorting
	//(Artciles are defined within the settings config file)
	void ignoreLeadingArticles(std::string &name1, std::string &name2) {

		if (Settings::getInstance()->getBool("IgnoreLeadingArticles"))
		{

			std::vector<std::string> articles = Utils::String::delimitedStringToVector(Settings::getInstance()->getString("LeadingArticles"), ",");

			for(Utils::String::stringVector::iterator it = articles.begin(); it != articles.end(); it++)
			{
			
				if (Utils::String::startsWith(Utils::String::toUpper(name1), Utils::String::toUpper(it[0]) + " ")) {
					name1 = Utils::String::replace(Utils::String::toUpper(name1), Utils::String::toUpper(it[0]) + " ", "");
				}

				if (Utils::String::startsWith(Utils::String::toUpper(name2), Utils::String::toUpper(it[0]) + " ")) {
					name2 = Utils::String::replace(Utils::String::toUpper(name2), Utils::String::toUpper(it[0]) + " ", "");
				}

			}

		}

	}

};
