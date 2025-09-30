#include "OutputWriter.h"
#include <iostream>

OutputWriter::OutputWriter(const std::string& outputPath, double fps, cv::Size size)
    : writer(outputPath, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, size)
{
    if (!writer.isOpened()) {
        std::cout << "Error: Couldn't open output video at " << outputPath << std::endl;
    }
}

OutputWriter::~OutputWriter() {
    if (writer.isOpened()) writer.release();
}

void OutputWriter::writeFrame(const cv::Mat& frame) {
    if (writer.isOpened()) writer.write(frame);
}

bool OutputWriter::isOpened() const {
    return writer.isOpened();
}
