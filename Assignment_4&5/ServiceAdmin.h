#pragma once

#include "Dog.h"
#include "RepoShelterDogs.h"

class ServiceAdmin {
private:
    RepoShelterDogs& repoShelter;
public:
    explicit ServiceAdmin(RepoShelterDogs& repoShelterDogs);
    ~ServiceAdmin();
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void deleteDog(const std::string &name);
    void updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph);
    DynamicVector<Dog> getDogs() const;

    /// get the position of a dog in the repoShelter
    int getDogPosition(const Dog &dog);
    int getDogPositionByName(const std::string &name);

    /// get the dog with the given name
    Dog getDogByName(const std::string &name);


};


