#ifndef _HELPERS_H_
#define _HELPERS_H_

size_t getFileSize(std::ifstream& file)
{
	size_t current = file.tellg();
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(current, std::ios::beg);

	return size;
}

void transformNonLetters(std::string& str, char replacement = '-')
{
	for (char& c : str)
	{
		if (!std::isalpha(static_cast<unsigned char>(c)))
		{
			c = '-';
		}
	}
}

std::string findMostCommon(const std::unordered_map<std::string, int>& candidates)
{
	std::pair<std::string, int> maxPair = { "", 0 };

	for (const auto& candidate : candidates)
	{
		if (candidate.second > maxPair.second)
		{
			maxPair = candidate;
		}
	}

	return maxPair.first;
}

#endif // !_HELPERS_H_