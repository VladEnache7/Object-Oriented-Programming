#pragma once
#include <string>
#include "Dog.h"
#include <vector>
#include "RepoShelterDogs.h"
#include "RepoAdoptedDogs.h"

class ServiceUser {
private:
    RepoShelterDogs &repoShelter;
    RepoAdoptedDogs *repoAdopted; // pointer to the repoAdopted in order to be able to change the type of the file
    std::string shelterFile;
    std::string adoptedFile;
    int indexCurrentDog = 0;
public:
    // constructor
    ServiceUser(RepoShelterDogs &repoShelter_, RepoAdoptedDogs *repoAdopted, std::string shelterFile_ = "ShelterDogs.txt", std::string adoptedFile_ = "AdoptedDogs.txt");

    // destructor
    ~ServiceUser() = default;

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

    // read and save shelter dogs from/to file
    void readShelterDogFromFile();
    void saveShelterDogToFile();

    // read and save adopted dogs from/to file
    void readAdoptedDogFromFile();
    void saveAdoptedDogToFile();

    RepoAdoptedDogs *const getRepoAdopted() const {
        return repoAdopted;
    }

    void setRepoAdopted(RepoAdoptedDogs *repoAdoptedToBeSet) {
        ServiceUser::repoAdopted = repoAdoptedToBeSet;
    }
};


