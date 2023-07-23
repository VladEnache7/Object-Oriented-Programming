#include "Tests.h"
#include "UserInterface.h"

using namespace std;


int main()
{
    Tests tests;
    tests.testAll();
    RepoShelterDogs repoShelter;
    RepoAdoptedDogs repoAdopted;
    ServiceAdmin serviceAdmin(repoShelter);
    ServiceUser serviceUser(repoShelter, repoAdopted);
    UserInterface userInterface(serviceAdmin, serviceUser);
    userInterface.run();
    return 0;
}

