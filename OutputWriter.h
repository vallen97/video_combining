#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include <opencv2/opencv.hpp>
#include <string>

class OutputWriter {
public:
    OutputWriter(const std::string& outputPath, double fps, cv::Size size);
    ~OutputWriter();
    void writeFrame(const cv::Mat& frame);
    bool isOpened() const;
private:
    cv::VideoWriter writer;
};

#endif
