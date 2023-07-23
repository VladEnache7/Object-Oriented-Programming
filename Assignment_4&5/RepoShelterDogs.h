#pragma once
#include "Dog.h"
#include "DynamicVector.h"

class RepoShelterDogs {
private:
    DynamicVector<Dog> dogs;

public:
    RepoShelterDogs();
    ~RepoShelterDogs();
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void deleteDog(const std::string &name);
    void updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph);
    DynamicVector<Dog> getDogs() const;
    int getDogPosition(const Dog& dog);
    int getDogPositionByName(const std::string& name);
    Dog getDogByName(const std::string& name);
};

