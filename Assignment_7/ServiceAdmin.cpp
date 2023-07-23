//
// Created by Admin on 26-Mar-23.
//
#include <fstream>
#include <iostream>
#include <utility>
#include "ServiceAdmin.h"
#include "Exceptions.h"
using namespace std;


ServiceAdmin::ServiceAdmin(RepoShelterDogs &repoShelterDogs,string  shelterFile_) : repoShelter(repoShelterDogs), shelterFile(std::move(shelterFile_)){}

void ServiceAdmin::addDog(const string &name, const string &breed, int age, const string &photograph) {
    // validate the dog before adding it - see if the dog already exists
    if (ServiceValidator::validateDogExists(this->repoShelter.getDogs(), name)) {
        throw ServiceException(
                "A dog with this name already exists and cannot be added! (consider adding a number at the end of the name)");
    }

    // then simply add the dog
    this->repoShelter.addDog(name, breed, age, photograph);

    // save the shelter file
    this->saveShelterDogToFile();
}


void ServiceAdmin::addDog(const Dog &dog) {
    // validate the dog before adding it - see if the dog already exists
    if (ServiceValidator::validateDogExists(this->repoShelter.getDogs(), dog.getName())) {
        throw ServiceException(
                "A dog with this name already exists and cannot be added! (consider adding a number at the end of the name)");
    }

    // then simply add the dog
    this->repoShelter.addDog(dog);

    // save the shelter file
    this->saveShelterDogToFile();
}

void ServiceAdmin::deleteDog(const string &name) {
    // validate the dog before deleting it - see if the dog exists
    int position = this->getDogPositionByName(name);
    if (!ServiceValidator::validateDogExists(this->repoShelter.getDogs(), name)) {
        throw ServiceException("The dog does not exist and cannot be deleted!");
    }
    // then simply delete the dog
    this->repoShelter.deleteDog(name);

    // save the shelter file
    this->saveShelterDogToFile();
}

void ServiceAdmin::updateDog(const string &name, const string &newBreed, int newAge,
                             const string &newPhotograph) {
    // validate the dog before updating it - see if the dog exists
    if (!ServiceValidator::validateDogExists(this->repoShelter.getDogs(), name)) {
        throw ServiceException("The dog with this name does not exist and cannot be updated!");
    }
    // then simply update the dog
    this->repoShelter.updateDog(name, newBreed, newAge, newPhotograph);

    // save the shelter file
    this->saveShelterDogToFile();
}

vector<Dog> ServiceAdmin::getDogs() const {
    return this->repoShelter.getDogs();
}

int ServiceAdmin::getDogPosition(const Dog &dog) {
    return this->repoShelter.getDogPosition(dog);
}

int ServiceAdmin::getDogPositionByName(const string &name) {
    return this->repoShelter.getDogPositionByName(name);
}

Dog ServiceAdmin::getDogByName(const string &name) {
    int position = this->getDogPositionByName(name);
    if (position == -1) {
        throw Exception("The dog does not exist!");
    }
    return this->repoShelter.getDogs()[position];
}

void ServiceAdmin::readShelterDogFromFile() {
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

void ServiceAdmin::saveShelterDogToFile() {
    ofstream file(shelterFile);
    if (!file.is_open()) {
        throw Exception("The file could not be opened!");
    }
    for (const auto &dog: this->repoShelter.getDogs()) {
        file << dog;
    }
    file.close();

}

bool ServiceValidator::validateDogExists(const vector<Dog> &dogs, const string &name) {
    for (const auto &dog: dogs) {
        if (dog.getName() == name) {
            return true;
        }
    }
    return false;
}
