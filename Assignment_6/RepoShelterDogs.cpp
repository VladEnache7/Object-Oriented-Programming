#include "RepoShelterDogs.h"

RepoShelterDogs::RepoShelterDogs() {
    this->dogs = std::vector<Dog>();
}

RepoShelterDogs::~RepoShelterDogs() = default;

void RepoShelterDogs::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    this->dogs.emplace_back(name, breed, age, photograph);
}

void RepoShelterDogs::deleteDog(const std::string &name) {
    int position = this->getDogPositionByName(name);
    // delete dog from stl vector
    this->dogs.erase(this->dogs.begin() + position);
}

void RepoShelterDogs::updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph) {
    Dog updatedDog = Dog(name, newBreed, newAge, newPhotograph);
    int position = getDogPositionByName(name);
    this->dogs[position] = updatedDog;
}

std::vector<Dog> RepoShelterDogs::getDogs() const {
    return this->dogs;
}

int RepoShelterDogs::getDogPosition(const Dog &dog) {
    for (int i = 0; i < this->dogs.size(); i++) {
        if (this->dogs[i] == dog) {
            return i;
        }
    }
    return -1;
}

int RepoShelterDogs::getDogPositionByName(const std::string &name) {
    for (int i = 0; i < this->dogs.size(); i++) {
        if (this->dogs[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

Dog RepoShelterDogs::getDogByName(const std::string &name) {
    for (auto & dog : this->dogs) {
        if (dog.getName() == name) {
            return dog;
        }
    }
    return {};
}