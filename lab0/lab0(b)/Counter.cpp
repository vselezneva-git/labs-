#include "Counter.h"
#include <algorithm>

void Counter::addWords(std::list<std::string>& words)
{
    for(const std::string& word : words)
    {
        if(!word.empty())
        {
            wordCount[word]++;
            sumWords++;
        }
    }
}

int Counter::getSumWords() const
{
    return sumWords;
}

std::vector<std::pair<std::string, int>> Counter::getSortedWords() const
{
    std::vector<std::pair<std::string, int>> sortWords(wordCount.begin(), wordCount.end());

    std::sort(sortWords.begin(), sortWords.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    return sortWords;
}