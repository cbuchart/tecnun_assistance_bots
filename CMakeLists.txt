cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        NO)

option(FIND_DATES_USING_REGEX "Compile CalendarBot with support for regular expressions. This is only for illustrative purposes since it is much slower than the manual search." OFF)

if(FIND_DATES_USING_REGEX)
    add_definitions(-DFIND_DATES_USING_REGEX)
endif(FIND_DATES_USING_REGEX)

project(tecnun_notes_app)

set(COMMON_SOURCES
    src/Date.cpp
    src/ClassificationBot.cpp
    src/CalendarBot.cpp
    src/BotWorker.cpp
    src/utils.cpp
)

set(BASIC_SOURCES
    ${COMMON_SOURCES}
    src/main_basic.cpp
)
add_executable(${PROJECT_NAME}_basic ${BASIC_SOURCES})

set(EXTENDED_SOURCES
    ${COMMON_SOURCES}
    src/Broker.cpp
    src/main_extended.cpp
)
add_executable(${PROJECT_NAME}_extended ${EXTENDED_SOURCES})
