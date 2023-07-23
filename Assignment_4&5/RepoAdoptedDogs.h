#pragma once

#include "Dog.h"
#include "DynamicVector.h"

class RepoAdoptedDogs {
private:
    DynamicVector<Dog> dogs;
public:
//    RepoAdoptedDogs(); // default constructor
//    ~RepoAdoptedDogs(); // default destructor
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void addDog(const Dog &dog);
    DynamicVector<Dog> getDogs() const;

};
