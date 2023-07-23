cmake_minimum_required(VERSION 3.23)
project(a45_912_enache_vlad CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(a45_912_enache_vlad
        main.cpp DynamicVector.cpp DynamicVector.h Tests.cpp Tests.h Dog.cpp Dog.h RepoShelterDogs.cpp RepoShelterDogs.h ServiceAdmin.cpp ServiceAdmin.h Exceptions.cpp Exceptions.h UserInterface.cpp UserInterface.h ServiceUser.cpp ServiceUser.h RepoAdoptedDogs.cpp RepoAdoptedDogs.h)
