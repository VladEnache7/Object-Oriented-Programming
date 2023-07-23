cmake_minimum_required(VERSION 3.22)
project(a7_912_enache_vlad_1 CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(a7_912_enache_vlad_1
        Dog.cpp
        Dog.h
        Exceptions.cpp
        Exceptions.h
        main.cpp
        RepoAdoptedDogs.cpp
        RepoAdoptedDogs.h
        RepoShelterDogs.cpp
        RepoShelterDogs.h
        ServiceAdmin.cpp
        ServiceAdmin.h
        ServiceUser.cpp
        ServiceUser.h
        Tests.cpp
        Tests.h
        UserInterface.cpp
        UserInterface.h)

#target_link_libraries(a7_912_enache_vlad_1 LINK_PUBLIC sqlite3)
