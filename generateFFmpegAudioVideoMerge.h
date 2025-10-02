#pragma once
#ifndef FFMPEG_AUDIO_VIDEO_MERGE_H
#define FFMPEG_AUDIO_VIDEO_MERGE_H

#include <string>
#include <vector>

void generateFFmpegAudioVideoMerge(const std::vector<std::string>& inputVideos,
	const std::string& silentVideoPath,
	const std::string& finalOutputPath,
	const std::string& batchFileName = "merge_audio_video.bat");

#endif 
