
#include "ServiceUser.h"

ServiceUser::ServiceUser(RepoShelterDogs &repoShelter, RepoAdoptedDogs &repoAdopted) : repoShelter(repoShelter),
                                                                                               repoAdopted(repoAdopted) {}

DynamicVector<Dog> ServiceUser::getDogsShelter() {
    return this->repoShelter.getDogs();
}

DynamicVector<Dog> ServiceUser::getDogsAdopted() {
    return this->repoAdopted.getDogs();
}

DynamicVector<Dog> ServiceUser::getDogsFiltered(const std::string &breed, int age) {
    DynamicVector<Dog> unfilteredDogs = getDogsShelter();
    DynamicVector<Dog> filteredDogs;
    for (int i = 0; i < unfilteredDogs.getSize(); i++) {
        Dog currentDog = unfilteredDogs[i];
        if ((currentDog.getBreed() == breed  || breed.empty()) && currentDog.getAge() < age) {
            filteredDogs.addElement(currentDog);
        }
    }
    return filteredDogs;
}

Dog ServiceUser::getCurrentDog() {
    // I have made the check in the UI
    return this->getDogsShelter()[this->indexCurrentDog];
}

void ServiceUser::goToTheNextDog() {
    // if the index is the last one, then we go back to the first one
    this->indexCurrentDog = (this->indexCurrentDog + 1) % this->getDogsShelter().getSize();
}

void ServiceUser::adoptDog(const std::string &name) {
    Dog dog = this->repoShelter.getDogByName(name);
    // call the other adoptDog function
    this->adoptDog(dog);
}

void ServiceUser::adoptDog(const Dog& dog) {
    // remove dog from shelter
    this->repoShelter.deleteDog(dog.getName());
    // add dog to adopted list
    this->repoAdopted.addDog(dog);

}

ServiceUser::~ServiceUser() = default;
