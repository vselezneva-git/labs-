#include "App.h"
#include <iostream>

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