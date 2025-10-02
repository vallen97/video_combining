#include "DirectoryReader.h"
#include <filesystem>
#include <algorithm>

DirectoryReader::DirectoryReader(const std::string& directoryPath)
	: directoryPath(directoryPath) {
}

DirectoryReader::~DirectoryReader() {}

std::vector<std::string> DirectoryReader::getVideoFiles() const {
	std::vector<std::string> videoExtensions = {
		"webm","mkv","flv","vob","ogv","ogg","rrc","gifv","mng","mov",
		"avi","qt","wmv","yuv","rm","asf","amv","mp4","m4p","m4v",
		"mpg","mp2","mpeg","mpe","mpv","svi","3gp","3g2","mxf","roq",
		"nsv","f4v","f4p","f4a","f4b","mod","ts"
	};
	std::vector<std::string> fileNames;
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.is_regular_file()) {
			std::string path = entry.path().string();
			for (const std::string& ext : videoExtensions) {
				if (path.size() > ext.size() &&
					path.substr(path.size() - ext.size() - 1) == "." + ext) {
					fileNames.push_back(path);
					break;
				}
			}
		}
	}
	std::sort(fileNames.begin(), fileNames.end());
	return fileNames;
}
