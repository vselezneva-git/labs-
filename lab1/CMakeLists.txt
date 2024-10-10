cmake_minimum_required(VERSION 3.10)

# Название проекта
project(labaa)

# Стандарт языка C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем файлы с исходным кодом
add_executable(labaa
    main.cpp
    BitArray.cpp
)

# Заголовочные файлы
target_include_directories(labaa PUBLIC
    ${PROJECT_SOURCE_DIR}
)
