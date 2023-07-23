//
// Created by Admin on 26-Mar-23.
//

#include "Dog.h"
#include "Exceptions.h"
#include <iostream>

using namespace std;

// default constructor
Dog::Dog() {
    this->breed = "";
    this->name = "";
    this->age = 0;
    this->photograph = "";
}

// constructor with parameters
Dog::Dog(const string &name, const string &breed, int age, const string &photograph) {
    this->breed = breed;
    this->name = name;
    this->age = age;
    this->photograph = photograph;
}

// copy constructor is used because there are no pointers in the clas
Dog::Dog(const Dog &otherDog) = default;

// the default destructor is used because there are no pointers in the class
Dog::~Dog() {

}

// the default operator = is used because there are no pointers in the class
Dog& Dog::operator=(const Dog &otherDog) = default;

/**
 * Getter for the breed of the dog
 * @return the breed of the dog
 */
string Dog::getBreed() const { // const means that the function will not modify the object
    return this->breed;
}

/**
 * Getter for the name of the dog
 * @return the name of the dog
 */
string Dog::getName() const {
    return this->name;
}

/**
 * Getter for the age of the dog
 * @return the age of the dog
 */
int Dog::getAge() const {
    return this->age;
}

/**
 * Getter for the photograph of the dog
 * @return the photograph of the dog
 */
string Dog::getPhotograph() const {
    return this->photograph;
}

/**
 * Setter for the breed of the dog
 * @param newBreed - the new breed of the dog
 */
void Dog::setBreed(const string &newBreed) {
    this->breed = newBreed;
}

/**
 * Setter for the name of the dog
 * @param newName - the new name of the dog
 */
void Dog::setName(const string &newName) {
    this->name = newName;
}

/**
 * Setter for the age of the dog
 * @param newAge - the new age of the dog
 */
void Dog::setAge(const int newAge) {
    this->age = newAge;
}

/**
 * Setter for the photograph of the dog
 * @param newPhotograph - the new photograph of the dog
 */
void Dog::setPhotograph(const string &newPhotograph) {
    this->photograph = newPhotograph;
}

/**
 * Overload the == operator in order to compare two dogs
 * @param otherDog - the other dog
 * @return true if the two dogs are equal, false otherwise
 */
bool Dog::operator==(const Dog &otherDog) const {
    return this->breed == otherDog.breed && this->name == otherDog.name && this->age == otherDog.age && this->photograph == otherDog.photograph;
}

ostream &operator<<(ostream &os, const Dog &dog) {
    if (&os == &cout)
        os << "Name: " ;
    os  << dog.name << "\n";
    if (&os == &cout)
        os << "Breed: ";
    os << dog.breed << "\n";
    if (&os == &cout)
        os << "Age: ";
    os << dog.age << "\n";
    if (&os == &cout)
        os << "Photograph: ";
    os << dog.photograph << "\n";
    return os;
}

//TODO: there may be more to be done here
istream &operator>>(istream &is, Dog& dog) {

    string name, breed, stringAge, photograph;
    
    if (&is == &cin) {
        cout << "Name: ";
        getchar();
    }
    getline(is, name); // TODO: this may be needed to be done with getline() instead of >>
    if (name == "\n" || name.empty())
        throw Exception("-"); /// because the last line is empty cout nothing

    if (&is == &cin)
        cout << "Breed: ";
    getline(is, breed);

    if (&is == &cin)
        cout << "Age: ";
    getline(is, stringAge);
    if(stringAge.find('\r') != string::npos)
        stringAge.erase(stringAge.find('\r'), 1);

    if (&is == &cin)
        while (!DogValidator::validateAge(stringAge)) {
            cout << "Invalid age! Please enter a valid age: ";
            is >> stringAge;
        }
    else if (!DogValidator::validateAge(stringAge))
        throw Exception("There is something wrong with the age!(in the file probabily)");

    int age = stoi(stringAge);
    if (&is == &cin)
        cout << "Photograph: ";
    getline(is, photograph);

    dog.setName(name);
    dog.setBreed(breed);
    dog.setAge(age);
    dog.setPhotograph(photograph);

    return is;
}


bool DogValidator::validateAge(const string& stringAge) {
    if (stringAge.find_first_not_of("0123456789") != string::npos) {
        return false;
    } else if (stoi(stringAge) < 0 || stoi(stringAge) > 20) {
        return false;
    }
    return true;
}
