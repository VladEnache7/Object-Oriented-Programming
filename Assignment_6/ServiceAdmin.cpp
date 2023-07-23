//
// Created by Admin on 26-Mar-23.
//
#include "ServiceAdmin.h"
#include "Exceptions.h"


ServiceAdmin::ServiceAdmin(RepoShelterDogs& repoShelterDogs) : repoShelter(repoShelterDogs) {
    // nothing else to do
}

ServiceAdmin::~ServiceAdmin() = default;
// if the above gives an error, I will use the commented code
/*ServiceAdmin::~ServiceAdmin(){

}*/


void ServiceAdmin::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    // validate the dog before adding it - see if the dog already exists
    if (this->getDogPositionByName(name) != -1) {
        throw Exception("A dog with this name already exists and cannot be added! (consider adding a number at the end of the name)");
    }

    // then simply add the dog
    this->repoShelter.addDog(name, breed, age, photograph);
}

void ServiceAdmin::deleteDog(const std::string &name) {
    // validate the dog before deleting it - see if the dog exists
    int position = this->getDogPositionByName(name);
    if (position == -1) {
        throw Exception("The dog does not exist and cannot be deleted!");
    }
    // then simply delete the dog
    this->repoShelter.deleteDog(name);
}

void ServiceAdmin::updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph) {
    // validate the dog before updating it - see if the dog exists
    if (this->getDogPositionByName(name) == -1) {
        throw Exception("The dog with this name does not exist and cannot be updated!");
    }
    // then simply update the dog
    this->repoShelter.updateDog(name, newBreed, newAge, newPhotograph);
}

std::vector<Dog> ServiceAdmin::getDogs() const {
    return this->repoShelter.getDogs();
}

int ServiceAdmin::getDogPosition(const Dog &dog) {
    return this->repoShelter.getDogPosition(dog);
}

int ServiceAdmin::getDogPositionByName(const std::string &name) {
    return this->repoShelter.getDogPositionByName(name);
}

Dog ServiceAdmin::getDogByName(const std::string &name) {
    int position = this->getDogPositionByName(name);
    if (position == -1) {
        throw Exception("The dog does not exist!");
    }
    return this->repoShelter.getDogs()[position];
}
