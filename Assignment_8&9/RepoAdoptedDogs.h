#pragma once

#include "Dog.h"
#include <vector>



class RepoAdoptedDogs {
private:
    std::vector<Dog> dogs;
public:
//    RepoAdoptedDogs(); // default constructor
//    ~RepoAdoptedDogs(); // default destructor
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void addDog(const Dog &dog);
    std::vector<Dog> getDogs() const;

    virtual void write() {};

    virtual void display() {};

};

class RepoAdoptedDogsCSV : public RepoAdoptedDogs {
public:

    void write() override;

    void display() override;

};

class RepoAdoptedDogsHTML : public RepoAdoptedDogs {
public:

    void write() override;

    void display() override;
};