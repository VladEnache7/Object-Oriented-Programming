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


//RepoAdoptedSQLite::RepoAdoptedSQLite() {
//    int exit = 0;
//    exit = sqlite3_open("AdoptedDogs.db", &this->dogsDatabase);
//    if (exit) {
//        std::cerr << "Error open DB " << sqlite3_errmsg(this->dogsDatabase) << std::endl;
//        exit = sqlite3_close(this->dogsDatabase);
//    }
//    char *messageError;
//    std::string sql = "CREATE TABLE IF NOT EXISTS ADOPTEDDOGS("
//                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
//                      "NAME TEXT NOT NULL,"
//                      "BREED TEXT NOT NULL,"
//                      "AGE INTEGER NOT NULL,"
//                      "PHOTOGRAPH TEXT NOT NULL);";
//    exit = sqlite3_exec(this->dogsDatabase, sql.c_str(), NULL, 0, &messageError);
//    if (exit != SQLITE_OK) {
//        std::cerr << "Error Create Table" << std::endl;
//        sqlite3_free(messageError);
//    } else {
//        std::cout << "Table created Successfully" << std::endl;
//    }
//
//}
//
//RepoAdoptedSQLite::~RepoAdoptedSQLite() {
//    sqlite3_close(this->dogsDatabase);
//}
//
//void RepoAdoptedSQLite::write() {
//    char *messageError;
//    std::string sql = "DELETE FROM ADOPTEDDOGS;";
//    int exit = sqlite3_exec(this->dogsDatabase, sql.c_str(), nullptr, nullptr, &messageError);
//    if (exit != SQLITE_OK) {
//        std::cerr << "Error Delete" << std::endl;
//        sqlite3_free(messageError);
//    } else {
//        std::cout << "Records deleted Successfully!" << std::endl;
//    }
//    for (auto & dog : this->getDogs()){
//        sql = "INSERT INTO ADOPTEDDOGS (NAME, BREED, AGE, PHOTOGRAPH) VALUES ('" + dog.getName() + "', '" + dog.getBreed() + "', '" + std::to_string(dog.getAge()) + "', '" + dog.getPhotograph() + "');";
//        exit = sqlite3_exec(this->dogsDatabase, sql.c_str(), nullptr, nullptr, &messageError);
//        if (exit != SQLITE_OK) {
//            std::cerr << "Error Insert" << std::endl;
//            sqlite3_free(messageError);
//        } else {
//            std::cout << "Records created Successfully!" << std::endl;
//        }
//    }
//}
//
//void RepoAdoptedSQLite::display() {
//    system("start AdoptedDogs.db");
//}
