cmake_minimum_required(VERSION 3.0)

# 1. 定义项目名称
project(MAIN)

# 2. 自动收集 src 目录下的所有源文件，并存入变量 SRC_LIST
aux_source_directory(src SRC_LIST)

# 3. 添加 include 头文件搜索路径
include_directories(include)

# 4. 打印调试信息（非必需，但你的教程里有，我们保留它）
message(STATUS "This is BINARY dir: " ${MAIN_BINARY_DIR})
message(STATUS "This is SOURCE dir: " ${MAIN_SOURCE_DIR})

# 5. 告诉 CMake 用收集到的源文件生成名为 main 的可执行文件
add_executable(main ${SRC_LIST})