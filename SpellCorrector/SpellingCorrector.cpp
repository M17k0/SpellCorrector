#include <algorithm>

#include "SpellingCorrector.h"
#include "helpers.h"

// Make a dictionary that holds a counter of how often each word appears in the text file
void SpellingCorrector::loadDictionary(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::in);

	size_t length = getFileSize(file);

	std::string data(length, '\0');

	file.read(&data[0], length);

	transformNonLetters(data);

	for (size_t i = 0; i != std::string::npos;)
	{
		const size_t firstWord = data.find_first_not_of('-', i + 1);
		if (firstWord == std::string::npos)
			break;

		const size_t end = data.find('-', firstWord);
		dictionary[data.substr(firstWord, end - firstWord)]++;

		i = end;
	}
}

// Correct a word
std::string SpellingCorrector::correct(const std::string& word) 
{
    std::unordered_set<std::string> result;
    std::unordered_map<std::string, int> candidates;

    if (dictionary.find(word) != dictionary.end())
        return word;

    possibleEdits(word, result);
    filterKnown(result, candidates);

    if (!candidates.empty())
        return findMostCommon(candidates);

    for (const auto& editedWord : result) {
        std::unordered_set<std::string> subResult;

        possibleEdits(editedWord, subResult);
        filterKnown(subResult, candidates);

        if (!candidates.empty())
            return findMostCommon(candidates);
    }

    return "";
}

// Make all possible edits of a word
void SpellingCorrector::possibleEdits(const std::string& word, std::unordered_set<std::string>& result) 
{
    const std::string letters = "abcdefghijklmnopqrstuvwxyz";

    // Handle deletions
    for (std::string::size_type i = 0; i < word.size(); i++)
    {
        result.insert(word.substr(0, i) + word.substr(i + 1));
    }

    // Handle transpositions
    for (std::string::size_type i = 0; i < word.size() - 1; i++)
    {
        std::string transposed = word;
        std::swap(transposed[i], transposed[i + 1]);
        result.insert(transposed);
    }

    // Handle alterations and insertions
    for (char j : letters) 
    {
        for (std::string::size_type i = 0; i <= word.size(); i++) 
        {
            result.insert(word.substr(0, i) + j + word.substr(i));
            if (i < word.size() && word[i] != j)
                result.insert(word.substr(0, i) + j + word.substr(i + 1));
        }
    }
}

// Filters only the real words that are in the counter dictionary
void SpellingCorrector::filterKnown(const std::unordered_set<std::string>& edits, std::unordered_map<std::string, int>& knownWords) 
{
    for (const auto& word : edits) 
    {
        if (dictionary.find(word) != dictionary.end())
            knownWords.insert({ word, dictionary[word] });
    }
}