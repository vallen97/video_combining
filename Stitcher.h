#ifndef STITCHER_H
#define STITCHER_H

#include <string>
#include <vector>

class Stitcher {
public:
    Stitcher(const std::vector<std::string>& files, const std::string& outputPath);
    ~Stitcher();
    void execute();
private:
    std::vector<std::string> videoFiles;
    std::string outputVideo;
};

#endif
