cmake_minimum_required(VERSION 3.28)
project(Finger C)

set(CMAKE_C_STANDARD 11)

add_executable(Finger finger.c
        finger.h
        SOExplorer.c
        SOExplorer.h
        Print.c
        Print.h
)
