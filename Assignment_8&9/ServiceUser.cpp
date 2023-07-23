#include <fstream>
#include <iostream>
#include <utility>
#include "ServiceUser.h"
#include "Exceptions.h"
using namespace std;

ServiceUser::ServiceUser(RepoShelterDogs &repoShelter_, RepoAdoptedDogs *repoAdopted, std::string shelterFile_, std::string adoptedFile_)
        : repoShelter{repoShelter_}, shelterFile{std::move(shelterFile_)}, adoptedFile{std::move(adoptedFile_)} {
    this->repoAdopted = repoAdopted;
}


std::vector<Dog> ServiceUser::getDogsShelter() {
    return this->repoShelter.getDogs();
}

std::vector<Dog> ServiceUser::getDogsAdopted() {
    return this->repoAdopted->getDogs();
}

std::vector<Dog> ServiceUser::getDogsFiltered(const std::string &breed, int age) {
    std::vector<Dog> unfilteredDogs = getDogsShelter();
    std::vector<Dog> filteredDogs;
    for (const auto& currentDog : unfilteredDogs) {
        if ((currentDog.getBreed() == breed  || breed.empty()) && currentDog.getAge() < age) {
            filteredDogs.push_back(currentDog);
        }
    }
    return filteredDogs;
}

Dog ServiceUser::getCurrentDog() {
    // I have made the check in the UI
    return this->getDogsShelter()[this->indexCurrentDog];
}

void ServiceUser::goToTheNextDog() {
    // if the index is the last one, then we go back to the first one
    this->indexCurrentDog = (this->indexCurrentDog + 1) % this->getDogsShelter().size();
}

void ServiceUser::adoptDog(const std::string &name) {
    Dog dog = this->repoShelter.getDogByName(name);
    // call the other adoptDog function
    this->adoptDog(dog);

    // save changes to file
    this->saveShelterDogToFile();
    this->saveAdoptedDogToFile();
}

void ServiceUser::adoptDog(const Dog& dog) {
    // remove dog from shelter
    this->repoShelter.deleteDog(dog.getName());
    // add dog to adopted list
    this->repoAdopted->addDog(dog);

    // save changes to file
    this->saveShelterDogToFile();
    this->saveAdoptedDogToFile();
}

void ServiceUser::readShelterDogFromFile() {
    ifstream file(shelterFile);
    Dog dog{};
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    while (file.good()) {
        try{
            file >> dog;
            this->repoShelter.addDog(dog);
        }catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    file.close();
}

void ServiceUser::saveShelterDogToFile() {
    ofstream file(shelterFile);
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    for (const auto &dog: this->repoShelter.getDogs()) {
        file << dog;
    }
    file.close();
}

void ServiceUser::readAdoptedDogFromFile() {
    ifstream file(adoptedFile);
    Dog dog{};
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    while (file.good()) {
        try{
            file >> dog;
            this->repoAdopted->addDog(dog);
        }catch (exception& e) {
            cout << e.what() << endl;

        }
    }
    file.close();
}

void ServiceUser::saveAdoptedDogToFile() {
    ofstream file(adoptedFile);
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    for (const auto &dog: this->repoAdopted->getDogs()) {
        file << dog;
    }
    file.close();
}
