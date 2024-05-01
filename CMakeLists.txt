cmake_minimum_required(VERSION 3.19)
project(pmd2_dungeon_data_scraper)
#Provide the relevant enum and struct definitions to other projects
add_library(${PROJECT_NAME} dungeonDataBinaryExtractor.cpp dungeonDataBinaryExtractor.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
