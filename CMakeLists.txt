cmake_minimum_required(VERSION 3.10)
project(YuGiOh)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器选项
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# 包含目录
include_directories(include)

# 源文件
set(SOURCES
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Player.cpp
    src/Game.cpp
    src/CardDatabase.cpp
)

# 头文件
set(HEADERS
    include/Card.h
    include/Deck.h
    include/Player.h
    include/Game.h
    include/CardDatabase.h
)

# 创建可执行文件
add_executable(YuGiOh ${SOURCES} ${HEADERS})

# 如果需要链接其他库，可以在这里添加
# target_link_libraries(YuGiOh library_name)

# 设置输出目录
set_target_properties(YuGiOh PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 创建测试可执行文件（可选）
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
