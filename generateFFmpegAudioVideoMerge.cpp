#include <fstream>
#include <iostream>
#include <filesystem>

void generateFFmpegAudioVideoMerge(const std::vector<std::string>& inputVideos,
	const std::string& silentVideoPath,
	const std::string& finalOutputPath,
	const std::string& batchFileName) {
	if (inputVideos.empty()) {
		std::cerr << "No input videos provided for FFmpeg audio-video merge." << std::endl;
		return;
	}

	std::string listFileName = "ffmpeg_input_list.txt";

	// Create FFmpeg concat input list file
	std::ofstream listFile(listFileName);
	if (!listFile.is_open()) {
		std::cerr << "Failed to create list file: " << listFileName << std::endl;
		return;
	}

	for (const auto& path : inputVideos) {
		listFile << "file '" << path << "'\n";
	}
	listFile.close();


	std::string ffmpegCmd = "ffmpeg -f concat -safe 0 -i \"" + listFileName + "\" -i \"" + silentVideoPath +
		"\" -c:v copy -c:a aac -map 1:v:0 -map 0:a:0 -y \"" + finalOutputPath + "\"";


	std::ofstream batFile(batchFileName);
	if (!batFile.is_open()) {
		std::cerr << "Failed to create batch file: " << batchFileName << std::endl;
		return;
	}

	batFile << "@echo off\n";
	batFile << "echo Merging audio and video with FFmpeg...\n";
	batFile << ffmpegCmd << "\n";
	batFile << "pause\n";
	batFile.close();

	std::cout << "Batch file created: " << batchFileName << std::endl;
	std::cout << "Run this batch file to combine audio with your stitched video:" << std::endl;
	std::cout << ffmpegCmd << std::endl;
}
