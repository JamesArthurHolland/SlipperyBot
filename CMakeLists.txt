cmake_minimum_required(VERSION 3.6)
project(SlipperyBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Card.cpp Card.h Deck.cpp Deck.h Trick.cpp Trick.h Node.cpp Node.h ISMCTS.cpp ISMCTS.h)
add_executable(SlipperyBot ${SOURCE_FILES})