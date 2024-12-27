cmake_minimum_required(VERSION 3.29)
project(decrypting)

# Опция для выбора типа сборки библиотеки
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_CXX_STANDARD 20)

# Добавляем библиотеку decrypt
add_library(decrypt
        decrypt.cpp
)

# Указываем директорию для заголовков
target_include_directories(decrypt PUBLIC ${CMAKE_SOURCE_DIR})

# Исполняемые файлы и связывание с библиотекой
add_executable(main main.cpp)
add_executable(test test.cpp)

target_link_libraries(main PRIVATE decrypt)
target_link_libraries(test PRIVATE decrypt)
