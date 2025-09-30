#include "AlphaNumComparer.h"
#include <regex>
#include <cstdlib>

AlphaNumComparer::AlphaNumComparer() {
	// Constructor (no dynamic resources used)
}

AlphaNumComparer::~AlphaNumComparer() {
	// Destructor (no cleanup needed)
}

// Constructor of ParsedString: parse once on creation
AlphaNumComparer::ParsedString::ParsedString(const std::string& s) : original(s), numericSuffix(0) {
	static const std::regex re("(.*?)(\\d+)?\\.[^.]+$");
	std::smatch match;
	if (std::regex_match(s, match, re)) {
		alphaPrefix = match.str(1);
		if (match.size() > 2 && !match.str(2).empty()) {
			try {
				numericSuffix = std::stoi(match.str(2));
			}
			catch (...) {
				numericSuffix = 0;
			}
		}
	}
	else {
		auto pos = s.rfind('.');
		alphaPrefix = (pos != std::string::npos) ? s.substr(0, pos) : s;
	}
}

bool AlphaNumComparer::operator()(const ParsedString& a, const ParsedString& b) const {
	if (a.alphaPrefix != b.alphaPrefix) {
		return a.alphaPrefix < b.alphaPrefix;
	}
	return a.numericSuffix < b.numericSuffix;
}

int AlphaNumComparer::extractTrailingNumber(const std::string& s) const
{
	return 0;
}

std::string AlphaNumComparer::extractAlphaPrefix(const std::string& s) const
{
	return std::string();
}
