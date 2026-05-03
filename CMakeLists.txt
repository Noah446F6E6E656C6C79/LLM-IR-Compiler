cmake_minimum_required(VERSION 3.20)

project(compiler C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 1. Define your source files
set(SOURCES
        src/main.c
        src/lexer.c
        src/parser.c
)

# 2. Build the Executable FIRST
add_executable(compiler ${SOURCES})

# 3. Attach the Include Directory LAST (The Magic Line)
# ${CMAKE_SOURCE_DIR} guarantees CMake looks in the exact root folder of your project
target_include_directories(compiler PRIVATE ${CMAKE_SOURCE_DIR}/include)