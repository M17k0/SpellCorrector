#ifndef _HELPERS_H_
#define _HELPERS_H_

size_t getFileSize(std::ifstream& file)
{
	long current = file.tellg();
	file.seekg(0, std::ios::end);
	long size = file.tellg();
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

#endif // !_HELPERS_H_