cmake_minimum_required(VERSION 3.22)
project(a23_912_enache_vlad C)

set(CMAKE_C_STANDARD 11)

add_executable(a23_912_enache_vlad
        main.c UserInterface.c UserInterface.h Service.c Service.h Repository.c Repository.h  Medicine.h Medicine.c UndoRedoListOfOperations.c UndoRedoListOfOperations.h DynamicArray.c DynamicArray.h Tests.c Tests.h)
