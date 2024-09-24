#include "Reader.h"

Reader::Reader(const std::string& nameFile)
{
    inputFile.open(nameFile);
}

std::optional<std::string> Reader::getLine()
{
    if(!inputFile.is_open())
    {
        return std::nullopt;
    }

    std::string line;
    if(std::getline(inputFile, line))
    {
        return line;
    } else{
        return std::nullopt;
    }
}

void Reader::close()
{
    if(inputFile.is_open())
    {
        inputFile.close();
    }
}

Reader::~Reader()
{
    close();
}