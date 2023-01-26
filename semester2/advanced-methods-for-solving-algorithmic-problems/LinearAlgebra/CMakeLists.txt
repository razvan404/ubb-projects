cmake_minimum_required(VERSION 3.21)
project(LinearAlgebra)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(LinearAlgebra
        complex.c
        complex.h
        #LinearAlgebra.cpp
        main.c
        matrix.c
        matrix.h
        operations.c
        operations.h
        polynomial.c
        polynomial.h
        scalar.c
        scalar.h
        tests.c
        tests.h
        trigonometry.c
        trigonometry.h
        utils.c
        utils.h
        vector.c
        vector.h)
