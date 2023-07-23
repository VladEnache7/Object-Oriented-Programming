#include <iostream>
#include "Tests.h"
#include "UserInterface.h"

using namespace std;


int main()
{
//    system("start file:///C:/Users/Admin/Documents/GitHub/a7-912-enache-vlad-1/example.html");
    Tests tests;
    tests.testAll();
    RepoShelterDogs repoShelter;
    RepoAdoptedDogs* repoAdopted;
    {
        cout << "Which type of file do you want to use? (CSV/HTML): ";
        string fileType;
        cin >> fileType;
        if (fileType == "CSV") {
            repoAdopted = new RepoAdoptedDogsCSV;
        } else {
            repoAdopted = new RepoAdoptedDogsHTML;
        }
    }
    ServiceAdmin serviceAdmin(repoShelter);
    ServiceUser serviceUser(repoShelter, repoAdopted);
    UserInterface userInterface(serviceAdmin, serviceUser);
    userInterface.run();

    return 0;
}

