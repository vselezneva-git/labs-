cmake_minimum_required(VERSION 3.10)

# Название проекта
project(lab0b)

# Стандарт языка C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем файлы с исходным кодом
add_executable(lab0b
    main.cpp
    Reader.cpp
    Splitting.cpp
    Counter.cpp
    Writer.cpp
    App.cpp
)

# Заголовочные файлы
target_include_directories(lab0b PUBLIC
    ${PROJECT_SOURCE_DIR}
)
