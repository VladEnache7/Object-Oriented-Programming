#include "RepoAdoptedDogs.h"

void RepoAdoptedDogs::addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
    Dog dog = Dog(name, breed, age, photograph);
    this->dogs.push_back(dog);
}

std::vector<Dog> RepoAdoptedDogs::getDogs() const {
    return this->dogs;
}

void RepoAdoptedDogs::addDog(const Dog &dog) {
    this->dogs.push_back(dog);
}
