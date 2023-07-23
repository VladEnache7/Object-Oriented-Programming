#include "RepoAdoptedDogs.h"
#include <fstream>
#include <iostream>

using namespace std;

void RepoAdoptedDogs::addDog(const string &name, const string &breed, int age, const string &photograph) {
    Dog dog = Dog(name, breed, age, photograph);
    this->dogs.push_back(dog);
}

vector<Dog> RepoAdoptedDogs::getDogs() const {
    return this->dogs;
}

void RepoAdoptedDogs::addDog(const Dog &dog) {
    this->dogs.push_back(dog);
}

void RepoAdoptedDogsCSV::write() {
    ofstream writeToCSVFile("AdoptedDogs.csv");
    for (auto & i : this->getDogs()){
        writeToCSVFile << i.getName() << "," << i.getBreed() << "," << i.getAge() << "," << i.getPhotograph() << "\n";
    }
    writeToCSVFile.close();

}

void RepoAdoptedDogsCSV::display() {
    system("start AdoptedDogs.csv");
}

void RepoAdoptedDogsHTML::write() {
    ofstream writeToHTMLFile("AdoptedDogs.html");
    writeToHTMLFile << "<!DOCTYPE html>" << endl;
    writeToHTMLFile << "<html>" << endl;
    writeToHTMLFile << "<head>" << endl;
    writeToHTMLFile << "    <title>Adopted Dogs</title>" << endl;
    writeToHTMLFile << "</head>" << endl;
    writeToHTMLFile << "<body>" << endl;
    writeToHTMLFile << "<table border=\"1\">" << endl;

    writeToHTMLFile << "    <tr>" << endl;
    writeToHTMLFile << "        <td>Name</td>" << endl;
    writeToHTMLFile << "        <td>Breed</td>" << endl;
    writeToHTMLFile << "        <td>Age</td>" << endl;
    writeToHTMLFile << "        <td>Photograph</td>" << endl;
    writeToHTMLFile << "    </tr>" << endl;

    for (auto & i : this->getDogs()){
        writeToHTMLFile << "    <tr>" << endl;
        writeToHTMLFile << "        <td>"+i.getName()+"</td>" << endl;
        writeToHTMLFile << "        <td>"+i.getBreed()+"</td>" << endl;
        writeToHTMLFile << "        <td>" << i.getAge() << "</td>" << endl;
        writeToHTMLFile << "        <td><a href=\""+i.getPhotograph()+"\">Link</a></td>" << endl;
        writeToHTMLFile << "    </tr>" << endl;
    }

    writeToHTMLFile << "</table>" << endl;
    writeToHTMLFile << "</body>" << endl;
    writeToHTMLFile << "</html>" << endl;

    writeToHTMLFile.close();
}

void RepoAdoptedDogsHTML::display() {
    system( "start AdoptedDogs.html");
}

