cmake_minimum_required(VERSION 3.7)
project(cppOfflineMovieDatabase)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        main.cpp
        Movie.cpp
        Movie.h
        MovieDatabase.cpp
        MovieDatabase.h
        Rating.cpp
        Rating.h
        TimeStamp.cpp
        TimeStamp.h)

add_executable(cppOfflineMovieDatabase ${SOURCE_FILES})