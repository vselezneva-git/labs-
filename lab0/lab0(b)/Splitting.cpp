#include "Splitting.h"
#include <cctype>

std::list<std::string> Splitting::wordSplit(const std::string& line)
{
    std::list<std::string> words;
    std::string word;

    for(char ch : line)
    {
        if(std::isalnum(ch))
        {
            word += tolower(ch);
        }
        else{
            words.push_back(word);
            word.clear();
        }
    }
    if(!word.empty())
    {
        words.push_back(word);
    }


    return words;
}