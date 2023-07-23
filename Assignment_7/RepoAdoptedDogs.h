#pragma once

#include "Dog.h"
#include <vector>

//#include <sqlite3.h>

class RepoAdoptedDogs {
private:
    std::vector<Dog> dogs;
public:
//    RepoAdoptedDogs(); // default constructor
//    ~RepoAdoptedDogs(); // default destructor
    void addDog(const std::string &name, const std::string &breed, int age, const std::string &photograph);
    void addDog(const Dog &dog);
    std::vector<Dog> getDogs() const;

    virtual void write() = 0;

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

//class RepoAdoptedSQLite : public RepoAdoptedDogs {
//private:
//    sqlite3 *dogsDatabase;
//public:
//    RepoAdoptedSQLite();
//
//    ~RepoAdoptedSQLite();
//
//    void write() override;
//
//    void display() override;
//};