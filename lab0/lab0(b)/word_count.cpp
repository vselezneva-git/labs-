#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cctype>
#include <iomanip>

std::list<std::string> word_splitting(const std::string& line)
{
    std::list<std::string> words;
    std::string word;

    for(char b : line)
    {
        if(std::isalnum(b))
        {
            word += std::tolower(b);
        }
        else
        {
            if(!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
    }
    if(!word.empty())
    {
        words.push_back(word);
    }

    return words;
}


int main(int args, char* argv[]){
    if(args != 3)
    {
        std::cerr << "Ошибка: неверное количество аргументов.\n";
        std::cerr << "Ожидаемые данные: " << argv[0] << "input.txt output.csv.\n";
        return 1;
    }

    std::string name_input_file = argv[1];
    std::string name_output_file = argv[2];

    std::ifstream inputFile(name_input_file);
    if(!inputFile.is_open())
    {
        std::cerr << "Ошибка чтения файла: " << argv[1] << "\n";
        return 1;
    }

    std::list<std::string> lines;
    std::string line;

    while(std::getline(inputFile, line))
    {
        lines.push_back(line);
    }
    inputFile.close();

    //слово -> частота
    std::map <std::string, int> word_count;
    int sum_word = 0;

    for(const std::string& line : lines)
    {
        std::list<std::string> words = word_splitting(line);
            for(const auto& word : words)
        {
            word_count[word]++;
            sum_word++;
        }
    }


    std::ofstream outputFile(name_output_file);
    if(!outputFile.is_open())
    {
        std::cerr << "Ошибка записи в файл: " << name_input_file << "\n";
        return 1;
    }

    outputFile << "Слово  Частота  Частота(%)" << "\n";

    for(const auto& pair : word_count)
    {
        double freq_in_percent = static_cast<double>(pair.second) / sum_word * 100;
        outputFile << pair.first << "  " << pair.second << "  " << freq_in_percent << "%" << "\n";
    }

    outputFile.close();
    return 0;

}

