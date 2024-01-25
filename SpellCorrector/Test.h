#ifndef _TEST_H_
#define _TEST_H_

#include <vector>

#include "SpellingCorrector.h"

class Test
{
public:
	std::vector<std::pair<std::string, std::vector<std::string>>> readTestFile(const std::string& filename);
	Test(SpellingCorrector _corrector) : corrector(_corrector) {};

	void runTestFileTests(std::string fileName);

private:
	SpellingCorrector corrector;
};

#endif // !_TEST_H_
