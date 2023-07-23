#pragma once

#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;
public:
    /// Constructors and destructor
    // Default constructor
    Dog();
    // Constructor with parameters
    Dog(const std::string& name, const std::string& breed, int age, const std::string& photograph);
    // Copy constructor
    Dog(const Dog& otherDog);
    // Operator =
    Dog& operator=(const Dog& otherDog);
    // Destructor
    ~Dog();

    /// Getters
    std::string getBreed() const;
    std::string getName() const;
    int getAge() const;
    std::string getPhotograph() const;

    /// Setters
    void setBreed(const std::string& breed);
    void setName(const std::string& name);
    void setAge(int age);
    void setPhotograph(const std::string& photograph);

    /// Operators
    // Overload the == operator in order to compare two dogs
    bool operator==(const Dog& otherDog) const;
    //TODO: overload the << operator in order to print a dogToBePrinted
//    // Overload the << operator in order to print a dogToBe
//    friend std::istream& operator>>(std::istream& output, const Dog& dogToBePrinted);

};

