#include "Stitcher.h"
#include "OutputWriter.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>

Stitcher::Stitcher(const std::vector<std::string>& files, const std::string& outputPath)
	: videoFiles(files), outputVideo(outputPath) {
}

Stitcher::~Stitcher() {}

void Stitcher::execute() {
    std::unique_ptr<OutputWriter> writer;
    bool init = false;

    for (const auto& file : videoFiles) {
        std::cout << "Opening video file: " << file << std::endl;
        cv::VideoCapture cap(file, cv::CAP_FFMPEG);
        if (!cap.isOpened()) {
            std::cout << "Warning: Could not open video file: " << file << std::endl;
            continue;
        }

        double fps = cap.get(cv::CAP_PROP_FPS);
        int w = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int h = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        cv::Size size(w, h);

        if (!init) {
            writer = std::make_unique<OutputWriter>(outputVideo, fps, size);
            if (!writer->isOpened()) {
                std::cerr << "Error: Couldn't open output video at " << outputVideo << std::endl;
                return;
            }
            init = true;
        }

        cv::Mat frame;
        while (cap.read(frame)) {
            writer->writeFrame(frame);
        }
        cap.release();
    }

    std::cout << "Finished stitching, output: " << outputVideo << std::endl;
}