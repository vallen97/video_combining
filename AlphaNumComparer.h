#ifndef ALPHANUM_COMPARER_H
#define ALPHANUM_COMPARER_H

#include <string>

class AlphaNumComparer {
public:
	AlphaNumComparer();
	~AlphaNumComparer();

	// Parses and caches the split parts of a string for efficient repeated comparison
	struct ParsedString {
		std::string original;
		std::string alphaPrefix;
		int numericSuffix;

		ParsedString(const std::string& s);
	};

	// Comparison operator using cached parsed strings
	bool operator()(const ParsedString& a, const ParsedString& b) const;

private:
	int extractTrailingNumber(const std::string& s) const;
	std::string extractAlphaPrefix(const std::string& s) const;
};

#endif
