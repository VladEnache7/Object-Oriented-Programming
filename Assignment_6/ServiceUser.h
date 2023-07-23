#pragma once
#include <string>
#include "Dog.h"
#include <vector>
#include "RepoShelterDogs.h"
#include "RepoAdoptedDogs.h"

class ServiceUser {
private:
    RepoShelterDogs &repoShelter;
    RepoAdoptedDogs &repoAdopted;
    int indexCurrentDog = 0;
public:
    // constructor
    ServiceUser(RepoShelterDogs &repoShelter, RepoAdoptedDogs &repoAdopted);

    // destructor
    ~ServiceUser();

    // getters of the list of dogs
    std::vector<Dog> getDogsShelter();
    std::vector<Dog> getDogsAdopted();
    std::vector<Dog> getDogsFiltered(const std::string& breed, int age);

    // add a dog to the list of adopted dogs
    void adoptDog(const std::string &name);
    void adoptDog(const Dog& dog);

    // get the current dog
    Dog getCurrentDog();

    // get the next dog
    void goToTheNextDog();
};


