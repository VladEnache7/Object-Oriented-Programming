#include "RepoShelterDogs.h"

RepoShelterDogs::RepoShelterDogs() {
    this->dogs = DynamicVector<Dog>();
}

RepoShelterDogs::~RepoShelterDogs() = default;

void RepoShelterDogs::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    this->dogs.addElement(Dog(name, breed, age, photograph));
}

void RepoShelterDogs::deleteDog(const std::string &name) {
    int position = this->getDogPositionByName(name);
    this->dogs.removeElementFromPosition(position);
}

void RepoShelterDogs::updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph) {
    Dog updatedDog = Dog(name, newBreed, newAge, newPhotograph);
    int position = getDogPositionByName(name);
    this->dogs.setElement(position, updatedDog);
}

DynamicVector<Dog> RepoShelterDogs::getDogs() const {
    return this->dogs;
}

int RepoShelterDogs::getDogPosition(const Dog &dog) {
    for (int i = 0; i < this->dogs.getSize(); i++) {
        if (this->dogs[i] == dog) {
            return i;
        }
    }
    return -1;
}

int RepoShelterDogs::getDogPositionByName(const std::string &name) {
    for (int i = 0; i < this->dogs.getSize(); i++) {
        if (this->dogs[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

Dog RepoShelterDogs::getDogByName(const std::string &name) {
    for (int i = 0; i < this->dogs.getSize(); i++) {
        if (this->dogs[i].getName() == name) {
            return this->dogs[i];
        }
    }
    return {};
}