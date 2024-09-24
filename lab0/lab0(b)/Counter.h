#ifndef COUNTER_H
#define COUNTER_H

#include <string>
#include <map>
#include <list>
#include <vector>

class Counter
{
private:
    std::map<std::string, int> wordCount;
    int sumWords = 0;

public:
    void addWords(std::list<std::string>& words);
    int getSumWords() const;
    std::vector<std::pair<std::string, int>> getSortedWords() const;
};

#endif