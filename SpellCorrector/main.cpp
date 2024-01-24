#include <iostream>
#include <fstream>
#include <sstream>

#include "SpellingCorrector.h"

SpellingCorrector corrector;

void Correct(const std::string& wrong, const std::string& expected)
{
	const bool isCorrect = corrector.correct(wrong) == expected;
	std::cout << "(" << wrong << ") == (" << expected << ") = (" << std::boolalpha << isCorrect << ")" << std::endl;
}

int main()
{


	// tests
	corrector.loadDictionary("big.txt");

	Correct("speling", "spelling"); // insert
	Correct("korrectud", "corrected"); // replace 2
	Correct("bycycle", "bicycle"); // replace
	Correct("inconvient", "inconvenient"); // insert 2
	Correct("arrainged", "arranged"); // delete
	Correct("peotry", "poetry"); // transpose
	Correct("peotryy", "poetry"); // transpose + delete
	Correct("word", "word"); // known
	Correct("quintessential", ""); // unknown
}