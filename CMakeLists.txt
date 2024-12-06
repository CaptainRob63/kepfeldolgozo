cmake_minimum_required(VERSION 3.29)
project(kepfeldolgozo C)

set(CMAKE_C_STANDARD 11)

add_executable(
        kepfeldolgozo main.c
        olvasas.c
        olvasas.h
        iras.c
        iras.h
        util.c
        util.h
        process.c
        process.h
)
