#include "SpellingCorrector.h"
#include "Test.h"

const std::string TEXT_FILE_DICTIONARY = "big.txt";
const std::string TEST_FILE = "spell-testset1.txt";

int main()
{
	SpellingCorrector corrector;
	corrector.loadDictionary(TEXT_FILE_DICTIONARY);
	Test test(corrector);

	// run tests
	test.runUserTests();

	test.runTestFileTests(TEST_FILE);

	return 0;
}