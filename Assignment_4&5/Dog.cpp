//
// Created by Admin on 26-Mar-23.
//

#include "Dog.h"
// default constructor
Dog::Dog() {
    this->breed = "";
    this->name = "";
    this->age = 0;
    this->photograph = "";
}

// constructor with parameters
Dog::Dog(const std::string &name, const std::string &breed, int age, const std::string &photograph) {
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
std::string Dog::getBreed() const { // const means that the function will not modify the object
    return this->breed;
}

/**
 * Getter for the name of the dog
 * @return the name of the dog
 */
std::string Dog::getName() const {
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
std::string Dog::getPhotograph() const {
    return this->photograph;
}

/**
 * Setter for the breed of the dog
 * @param newBreed - the new breed of the dog
 */
void Dog::setBreed(const std::string &newBreed) {
    this->breed = newBreed;
}

/**
 * Setter for the name of the dog
 * @param newName - the new name of the dog
 */
void Dog::setName(const std::string &newName) {
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
void Dog::setPhotograph(const std::string &newPhotograph) {
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

//TODO: overload the << operator in order to print a dogToBePrinted
/*
std::istream &operator>>(std::istream &output, const Dog &dogToBePrinted) {
    output << "Breed: " << dogToBePrinted.getBreed() << "\n";

}

std::ostream &operator<<(std::ostream &output, const Dog &dogToBePrinted) {
    output << "Breed: " << dogToBePrinted.getBreed() << "

}

*/
