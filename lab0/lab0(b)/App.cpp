#include "App.h"
#include "Reader.h"
#include "Splitting.h"
#include "Counter.h"
#include "Writer.h"

void App::start(const std::string& name_input_file, const std::string& name_output_file)
{
    Reader reader(name_input_file);
    Splitting splitter;
    Counter counter;
    Writer writer;
        
    while (true)
    {
        auto lineOpt = reader.getLine();
        if(!lineOpt.has_value())
        {
            break;
        }

        std::string line = lineOpt.value();
        std::list<std::string> words = splitter.wordSplit(line);
        counter.addWords(words);
        }

    std::vector<std::pair<std::string, int>> sortWords = counter.getSortedWords();

    auto writeResult = writer.writeCSV(name_output_file, sortWords, counter.getSumWords());

    if(!writeResult.has_value())
    {
        std::cerr << "Произошла ошибка при записи в файл" << "\n";
    }
}