cmake_minimum_required(VERSION 3.13)
project(missionariesAndCannibals2 C)

set(CMAKE_C_STANDARD 11)

add_executable(missionariesAndCannibals2 main.c main.h uninformed.h informed.h informed.c uninformed.c)