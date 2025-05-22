#pragma once

#include <string>
#include <vector>

//{ LevenshteinCalculator calc };

class CalSimilarity
{
public :
	bool IsSimiler(const std::string& a, const std::string& b);

private:
	int levenshtein(const std::string& a, const std::string& b);
};

