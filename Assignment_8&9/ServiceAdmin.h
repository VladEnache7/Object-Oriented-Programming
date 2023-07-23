#pragma once

#include "Dog.h"
#include "RepoShelterDogs.h"

class ServiceAdmin {
private:
    RepoShelterDogs& repoShelter;
    std::string shelterFile;
public:
    explicit ServiceAdmin(RepoShelterDogs& repoShelterDogs,std::string shelterFile_ = "ShelterDogs.txt");
    ~ServiceAdmin() = default;

    ///
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void addDog(const Dog &dog);
    void deleteDog(const std::string &name);
    void updateDog(const std::string &name, const std::string &newBreed, int newAge, const std::string &newPhotograph);
    std::vector<Dog> getDogs() const;

    /// get the position of a dog in the repoShelter
    int getDogPosition(const Dog &dog);
    int getDogPositionByName(const std::string &name);
    Dog getDogByName(const std::string &name);

    void readShelterDogFromFile();
    void saveShelterDogToFile();
};

class ServiceValidator {
public:
    static bool validateDogExists(const std::vector<Dog>& dogs, const std::string& name);
};

