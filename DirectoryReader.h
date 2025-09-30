#ifndef DIRECTORY_READER_H
#define DIRECTORY_READER_H

#include <string>
#include <vector>

class DirectoryReader {
public:
    explicit DirectoryReader(const std::string& directoryPath);
    ~DirectoryReader();
    std::vector<std::string> getVideoFiles() const;
private:
    std::string directoryPath;
};

#endif
