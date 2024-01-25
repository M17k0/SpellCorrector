#include <iomanip>
#include <stdio.h>
#include <time.h>

#include "Test.h"

std::vector<std::pair<std::string, std::vector<std::string>>> Test::readTestFile(const std::string& filename)
{
	std::vector<std::pair<std::string, std::vector<std::string>>> result;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return result;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string key;
		iss >> key;  // Read the word on the left of ':'

		std::vector<std::string> alternatives;
		std::string word;
		while (iss >> word) {
			alternatives.push_back(word);  // Read all words on the right of ':'
		}

		result.push_back(std::make_pair(key, alternatives));
	}

	file.close();
	return result;
}

void Test::runUserTests()
{
	CheckCorrect("speling", "spelling"); // insert
	CheckCorrect("korrectud", "corrected"); // replace 2
	CheckCorrect("bycycle", "bicycle"); // replace
	CheckCorrect("inconvient", "inconvenient"); // insert 2
	CheckCorrect("arrainged", "arranged"); // delete
	CheckCorrect("peotry", "poetry"); // transpose
	CheckCorrect("peotryy", "poetry"); // transpose + delete
	CheckCorrect("word", "word"); // known
	CheckCorrect("quintessential", ""); // unknown
	std::cout << '\n';
}

void Test::runTestFileTests(std::string filename)
{
	std::vector<std::pair<std::string, std::vector<std::string>>> spellData = readTestFile(filename);

	int countCorrect = 0;
	int allWordsCount = 0;

	time_t startSeconds;
	startSeconds = time(NULL);

	for (const auto& pair : spellData)
	{
		for (const auto& word : pair.second)
		{
			if (corrector.correct(word) == pair.first.substr(0, pair.first.size() - 1))
			{
				++countCorrect;
			}
			++allWordsCount;
		}
	}

	time_t endSeconds;
	endSeconds = time(NULL);

	time_t duration = endSeconds - startSeconds;
	double percentage = (static_cast<double>(countCorrect) / allWordsCount) * 100;

	std::cout << std::fixed << std::setprecision(2) << "Percentage Correct: " << percentage << "% at " << (allWordsCount / duration) << " words per second" << std::endl;
}

void Test::CheckCorrect(const std::string& wrong, const std::string& expected)
{
	const bool isCorrect = this->corrector.correct(wrong) == expected;
	std::cout << "(" << wrong << ") == (" << expected << ") = (" << std::boolalpha << isCorrect << ")" << std::endl;
}
