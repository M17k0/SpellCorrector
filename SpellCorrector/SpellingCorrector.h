#ifndef _SPELLINGCORRECTOR_H_
#define _SPELLINGCORRECTOR_H_

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>

class SpellingCorrector
{
public:
	void loadDictionary(const std::string& filename);
	std::string correct(const std::string& word);

private:
	std::unordered_map<std::string, int> dictionary;

	void possibleEdits(const std::string& word, std::unordered_set<std::string>& result);
	void filterKnown(const std::unordered_set<std::string>& edits, std::unordered_map<std::string, int>& knownWords);
};

#endif // !_SPELLINGCORRECTOR_H_
