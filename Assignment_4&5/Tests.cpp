
#include <cassert>
#include "Tests.h"
#include "DynamicVector.h"
#include "Dog.h"
#include "RepoShelterDogs.h"
#include "ServiceAdmin.h"
#include "Exceptions.h"
#include "RepoAdoptedDogs.h"
#include "ServiceUser.h"

void Tests::testDynamicVector() {
    // testing the constructor
    DynamicVector<int> v(5);
    // testing addElement
    v.addElement(1);
    v.addElement(2);
    v.addElement(3);
    v.addElement(4);
    v.addElement(5);

    // testing copy constructor and operator =
    DynamicVector<int> v2(v);
    DynamicVector<int> v3;
    v3 = v;
    assert(v.getSize() == 5);
    assert(v2.getSize() == 5);
    assert(v3.getSize() == 5);
    assert(v.getCapacity() == 5);
    assert(v2.getCapacity() == 5);
    assert(v3.getCapacity() == 5);
    for (int i = 0; i < 5; ++i) {
        assert(v[i] == i + 1);
        assert(v2[i] == i + 1);
        assert(v3[i] == i + 1);
    }

    // testing addElementToPosition
    v.addElementToPosition(6, 0);
    assert(v[0] == 6);

    // testing removeElementFromPosition
    v.removeElementFromPosition(0);
    assert(v[0] == 1);

    // testing removeCertainElement
    v.removeCertainElement(1);
    assert(v[0] == 2);

    // testing findElement
    assert(*v.findElement(2) == 2);
    assert(v.findElement(1) == nullptr);

    // test resize
    DynamicVector<int> v4(1);
    v4.addElement(1);
    v4.addElement(2);
    v4.addElement(3);
    assert(v4.getSize() == 3);
    assert(v4.getCapacity() == 4);
}

void Tests::testDog() {
    // testing constructor
    Dog d1("Rex", "German Shepherd", 3,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    assert(d1.getName() == "Rex");
    assert(d1.getBreed() == "German Shepherd");
    assert(d1.getAge() == 3);
    assert(d1.getPhotograph() == "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");

    // testing copy constructor
    Dog d2{d1};
    assert(d2.getName() == "Rex");
    assert(d2.getBreed() == "German Shepherd");
    assert(d2.getAge() == 3);
    assert(d2.getPhotograph() == "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    d2.setName("Rex2");
    assert(d2.getName() == "Rex2");

    // testing operator =
    Dog d3;
    d3 = d1;
    assert(d3.getName() == "Rex");
    assert(d3.getBreed() == "German Shepherd");
    assert(d3.getAge() == 3);
    assert(d3.getPhotograph() == "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");

    d3.setName("Rex3");
    d3.setBreed("German Shepherd2");
    d3.setAge(4);
    d3.setPhotograph("test.jpg");
    assert(d3.getName() == "Rex3");
    assert(d3.getBreed() == "German Shepherd2");
    assert(d3.getAge() == 4);
    assert(d3.getPhotograph() == "test.jpg");

    // testing operator ==
    d2.setName("Rex");
    assert(d2 == d1);
}

void Tests::testRepoShelterDogs() {
    // testing constructor
    RepoShelterDogs repo;
    assert(repo.getDogs().getSize() == 0);

    // testing addDog
    Dog d1("Rex", "German Shepherd", 3,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repo.addDog("Rex", "German Shepherd", 3,
                "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    assert(repo.getDogs().getSize() == 1);
    assert(repo.getDogs()[0] == d1);

    // testing removeDog
    repo.deleteDog("Rex");
    assert(repo.getDogs().getSize() == 0);

    // testing updateDog
    repo.addDog("Rex", "German Shepherd", 3,
                "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    Dog d2("Rex", "German Shepherd2", 4,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repo.updateDog("Rex", "German Shepherd2", 4, "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    assert(repo.getDogs().getSize() == 1);
    assert(repo.getDogs()[0] == d2);

    // testing getDogPosition
    assert(repo.getDogPosition(d2) == 0);
    assert(repo.getDogPosition(d1) == -1);

    // testing getDogByName not found
    assert(repo.getDogByName("Rex2") == Dog());

}

void Tests::testServiceAdmin() {
    // testing constructor
    RepoShelterDogs repoShelterDogs;
    ServiceAdmin serviceAdmin{repoShelterDogs};

    assert(serviceAdmin.getDogs().getSize() == 0);

    // testing addDog
    Dog d1("Rex", "German Shepherd", 3,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    serviceAdmin.addDog("Rex", "German Shepherd", 3,
                        "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    assert(serviceAdmin.getDogs().getSize() == 1);

    // testing exception addDog
    try {
        serviceAdmin.addDog("Rex", "German Shepherd", 3,
                            "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
        assert(false);
    } catch (Exception &e) {
        assert(true);
    }

    // testing removeDog
    serviceAdmin.deleteDog("Rex");
    assert(serviceAdmin.getDogs().getSize() == 0);

    // testing exception removeDog
    try {
        serviceAdmin.deleteDog("Rex");
        assert(false);
    } catch (Exception &e) {
        assert(true);
    }

    // testing updateDog
    serviceAdmin.addDog("Rex", "German Shepherd", 3,
                        "updatedPicture.jpg");
    serviceAdmin.updateDog("Rex", "German Shepherd2", 7, "updatedPicture.jpg");
    Dog d2("Rex", "German Shepherd2", 7, "updatedPicture.jpg");
    assert(serviceAdmin.getDogs().getSize() == 1);
    assert(serviceAdmin.getDogs()[0] == d2);

    // testing exception updateDog
    try {
        serviceAdmin.updateDog("FakeName", "German Shepherd2", 7, "updatedPicture.jpg");
        assert(false);
    } catch (Exception &e) {
        assert(true);
    }

    // testing getDogPosition
    assert(serviceAdmin.getDogPosition(d2) == 0);

    // testing getDogByName
    assert(serviceAdmin.getDogByName("Rex") == d2);

    //testing getDogByName exception
    try {
        serviceAdmin.getDogByName("FakeName");
        assert(false);
    } catch (Exception &e) {
        assert(true);
    }
}

void Tests::testRepoAdoptedDogs(){
    // testing constructor
    RepoAdoptedDogs repoAdoptedDogs;
    assert(repoAdoptedDogs.getDogs().getSize() == 0);

    // testing addDog
    Dog d1("Rex", "German Shepherd", 3,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repoAdoptedDogs.addDog("Rex", "German Shepherd", 3,
                           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    assert(repoAdoptedDogs.getDogs().getSize() == 1);
    assert(repoAdoptedDogs.getDogs()[0] == d1);

    // testing addDog directly
    Dog d2 = Dog("Rex2", "German Shepherd2", 4,
                 "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repoAdoptedDogs.addDog(d2);
    assert(repoAdoptedDogs.getDogs().getSize() == 2);
    assert(repoAdoptedDogs.getDogs()[1] == d2);
}

void Tests::testServiceUser(){
    // testing constructor
    RepoShelterDogs repoShelterDogs;
    RepoAdoptedDogs repoAdoptedDogs;
    ServiceUser serviceUser(repoShelterDogs, repoAdoptedDogs);
    assert(serviceUser.getDogsShelter().getSize() == 0);
    assert(serviceUser.getDogsAdopted().getSize() == 0);

    // testing adoptDog
    Dog d1("Rex", "German Shepherd", 3,
           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repoShelterDogs.addDog("Rex", "German Shepherd", 3,
                           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    serviceUser.adoptDog("Rex");
    assert(serviceUser.getDogsShelter().getSize() == 0);
    assert(serviceUser.getDogsAdopted().getSize() == 1);
    assert(serviceUser.getDogsAdopted()[0] == d1);

    // testing getDogsFiltered
    repoShelterDogs.addDog("Rex2", "German Shepherd", 3,
                           "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
    repoShelterDogs.addDog("Rex3", "German Shepherd", 3, "updatedPicture.jpg");
    repoShelterDogs.addDog("Rex4", "German Shepherd", 3, "updatedPicture.jpg");

    DynamicVector<Dog> dogsFiltered = serviceUser.getDogsFiltered("German Shepherd", 10);
    assert(dogsFiltered.getSize() == 3);
    assert(dogsFiltered[0] == Dog("Rex2", "German Shepherd", 3,
                                  "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg"));
    assert(dogsFiltered[1] == Dog("Rex3", "German Shepherd", 3, "updatedPicture.jpg"));
    assert(dogsFiltered[2] == Dog("Rex4", "German Shepherd", 3, "updatedPicture.jpg"));

    // testing getCurrentDog
    assert(serviceUser.getCurrentDog() == Dog("Rex2", "German Shepherd", 3,
                                             "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg"));
    serviceUser.goToTheNextDog();
    assert(serviceUser.getCurrentDog() == Dog("Rex3", "German Shepherd", 3, "updatedPicture.jpg"));

    // testing adoptDog se
}

void Tests::testAll() {
    this->testDynamicVector();
    this->testDog();
    this->testRepoShelterDogs();
    this->testServiceAdmin();
    this->testRepoAdoptedDogs();
    this->testServiceUser();
}