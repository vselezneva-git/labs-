#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cctype>
#include <iomanip>
#include <vector>
#include <algorithm>

class Reader
{
public:
    std::list<std::string> readFile(const std::string& nameFile)
    {
        std::ifstream inputFile(nameFile);
        std::list<std::string> lines;
        std::string line;

        if(!inputFile.is_open())
        {
            std::cerr << "Ошибка открытия файла: " << nameFile << "\n";
            return lines;
        }

        while(std::getline(inputFile, line))
        {
            lines.push_back(line);
        }
        inputFile.close();
        return lines;
    }
};

class Splitting
{
public:
    std::list<std::string> wordSplit(const std::string& line)
    {
        std::list<std::string> words;
        std::string word;

        for(char ch : line)
        {
            if(std::isalnum(ch))
            {
                word += tolower(ch);
            }
            else
            {
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
};

class Counter
{
private:
    std::map<std::string, int> wordCount;
    int sumWords = 0;

public:
    void addWords(std::list<std::string>& words)
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

    int getSumWords() const
    {
        return sumWords;
    }

    std::vector<std::pair<std::string, int>> getSortedWords() const
    {
        std::vector<std::pair<std::string, int>> sortWords(wordCount.begin(), wordCount.end());

       std::sort(sortWords.begin(), sortWords.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.second > b.second;
                  });

        return sortWords;
    }
};

class Writer
{
public:
    void writeCSV(const std::string& nameFile, const std::vector<std::pair<std::string, int>>& sortWord, int sumWord)
    {
        std::ofstream outputFile(nameFile);
        if(!outputFile.is_open())
        {
            std::cerr << "Ошибка записи в файл" << "\n";
            return;
        }

        outputFile << "Слово Частота Частота(%)" << "\n";

        for(const auto& pair : sortWord)
        {
            double freqInPercent = static_cast<double>(pair.second) / sumWord * 100;
            outputFile << pair.first << "   " << pair.second << "   " << freqInPercent << "%" << "\n";
        }

        outputFile.close();
    }
};

class App
{
private:
    Reader reader;
    Splitting splitter;
    Counter counter;
    Writer writer;

public:
    void start(const std::string& name_input_file, const std::string& name_output_file)
    {
        std::list<std::string> lines = reader.readFile(name_input_file);

        for(const std::string& line : lines)
        {
            std::list<std::string> words = splitter.wordSplit(line);
            counter.addWords(words);
        }

        std::vector<std::pair<std::string, int>> sortWords = counter.getSortedWords();

        writer.writeCSV(name_output_file, sortWords, counter.getSumWords());
    }
};

int main(int args, char* argv[])
{
     if(args != 3)
    {
        std::cerr << "Ошибка: неверное количество аргументов.\n";
        std::cerr << "Ожидаемые данные: " << argv[0] << "input.txt output.csv.\n";
        return 1;
    }

    std::string name_input_file = argv[1];
    std::string name_output_file = argv[2];

    App app;
    app.start(name_input_file, name_output_file);

    return 0;
}