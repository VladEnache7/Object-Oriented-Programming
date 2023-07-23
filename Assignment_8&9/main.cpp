#include <iostream>
#include <QPainter>
#include "Tests.h"
//#include "UserInterface.h"
#include "GUI.h"
using namespace std;


int main(int argc, char* argv[])
{
    /// Tests
    Tests tests;
    tests.testAll();

    /// Initialize the repositories
    RepoShelterDogs repoShelter;
    RepoAdoptedDogs *repoAdopted = nullptr;

    /// Initialize the services
    ServiceAdmin serviceAdmin(repoShelter);
    ServiceUser serviceUser(repoShelter, repoAdopted);

    /// Initialize the GUI
    QApplication app(argc, argv);
    GUI gui(serviceAdmin, serviceUser);

    /// Show the GUI
    gui.show();

    return app.exec();
}

