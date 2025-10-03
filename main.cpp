#include "DirectoryReader.h"
#include "Stitcher.h"
#include "AlphaNumComparer.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>


void testOpenCV(const std::string& videoFile) {
	cv::VideoCapture cap(videoFile);
	if (!cap.isOpened()) {
		std::cout << "Failed to open video file: " << videoFile << std::endl;
		return;
	}
	std::cout << "Video file opened successfully: " << videoFile << std::endl;

	cv::Mat frame;
	if (!cap.read(frame)) {
		std::cout << "Failed to read frame from video." << std::endl;
		return;
	}
	std::cout << "First frame read successfully." << std::endl;

	cv::imshow("Test Frame", frame);
	std::cout << "Press any key in the video window to close." << std::endl;
	cv::waitKey(0);

	cap.release();
	cv::destroyAllWindows();
}


std::filesystem::path getOrCreateCompletedStitchingDir() {
	// Get current executable path
	std::filesystem::path exePath = std::filesystem::current_path();

	// Construct path to "completed_stitching" folder in same directory
	std::filesystem::path completedDir = exePath / "completed_stitching";

	// Check if directory exists; if not, create it
	if (!std::filesystem::exists(completedDir)) {
		try {
			std::filesystem::create_directory(completedDir);
			std::cout << "Created directory: " << completedDir << std::endl;
		}
		catch (const std::filesystem::filesystem_error& e) {
			std::cerr << "Error creating directory: " << e.what() << std::endl;
		}
	}
	else {
		std::cout << "Directory already exists: " << completedDir << std::endl;
	}

	return completedDir;
}

int main() {
	// Testing if opencv can load a video and read and show the first frame
	/*
	{

		std::cout << "Opening: " << path << std::endl;
		cv::VideoCapture cap(path);
		if (!cap.isOpened()) {
			std::cerr << "Failed to open video file!" << std::endl;
			return -1;
		}

		{
			cv::Mat frame;
			if (cap.read(frame)) {
				std::cout << "Read first frame successfully." << std::endl;

				cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
				cv::imshow("First OpenCV Application", frame);
				cv::moveWindow("First OpenCV Application", 0, 45);
				cv::waitKey(0);
				cv::destroyAllWindows();
			}
			else {
				std::cerr << "Failed to read first frame." << std::endl;
			}
		}

		return 0;
	}
	*/
	{
		std::string path = "Full path to video folder";
		std::string completed_org = "FullPathTtoProjectFolder/video_combining/video_combining/completed_stitching/";

		std::filesystem::path completed = getOrCreateCompletedStitchingDir();
		std::cout << "Output folder set to: " << completed << std::endl;

		//// Now you can combine outputFolder with your filename to generate output paths
		std::filesystem::path outputFile = completed / "stitched_result.mp4";
		std::cout << "Full output video path: " << outputFile << std::endl;

		std::string output = completed_org + "stitched_result.mp4";
		//std::string output = completed << "stitched_result.mp4";

		DirectoryReader dirReader(path);
		std::vector<std::string> videos = dirReader.getVideoFiles();

		AlphaNumComparer comparer;

		// Preparse all strings once
		std::vector<AlphaNumComparer::ParsedString> parsedFiles;
		for (const auto& f : videos) {
			parsedFiles.emplace_back(f);
		}

		// Sort parsed strings using efficient comparator
		std::sort(parsedFiles.begin(), parsedFiles.end(), comparer);

		// Output original filenames in sorted order
		for (const auto& pf : parsedFiles) {
			std::cout << pf.original << "\n";
		}

		if (videos.empty()) {
			std::cout << "No video files found." << std::endl;
			return 1;
		}
		Stitcher stitcher(videos, output);
		stitcher.execute();

		//std::cout << cv::getBuildInformation() << std::endl;


		//testOpenCV(sampleVideoPath);

		return 0;
	}


}