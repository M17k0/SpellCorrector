#ifndef _TEST_H_
#define _TEST_H_
#include "SpellingCorrector.h"

#include <iostream>

class Test
{
public:
	std::vector<std::pair<std::string, std::vector<std::string>>> readTestFile(const std::string& filename);
	Test(SpellingCorrector _corrector) : corrector(_corrector) {};

	void runUserTests();
	void runTestFileTests(std::string fileName);
private:
	SpellingCorrector corrector;
	std::string testFileName;

	void CheckCorrect(const std::string& wrong, const std::string& expected);
};

#endif // !_TEST_H_
