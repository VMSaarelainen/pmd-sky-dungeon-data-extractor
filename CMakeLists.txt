cmake_minimum_required(VERSION 3.21)
project(pmd2_data_scraper)
if(PROJECT_IS_TOP_LEVEL)
    #build scraper executable
    find_package(nlohmann_json)
    add_executable(pmd2_data_scraper pmd2_dungeon_data_scraper/main.cpp)
    target_include_directories(${PROJECT_NAME} PRIVATE ${pmd2_dungeon_data_scraper_SOURCE_DIR}/pmd2_dungeon_data_scraper/)
else()
    #forward generator parameter definitions to parent project
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})  #Other projects linking in floor_props.hpp have to prefix the folder name
endif()
