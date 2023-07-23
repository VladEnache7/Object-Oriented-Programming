
#include "ServiceUser.h"

ServiceUser::ServiceUser(RepoShelterDogs &repoShelter, RepoAdoptedDogs &repoAdopted) : repoShelter(repoShelter),
                                                                                               repoAdopted(repoAdopted) {}

std::vector<Dog> ServiceUser::getDogsShelter() {
    return this->repoShelter.getDogs();
}

std::vector<Dog> ServiceUser::getDogsAdopted() {
    return this->repoAdopted.getDogs();
}

std::vector<Dog> ServiceUser::getDogsFiltered(const std::string &breed, int age) {
    std::vector<Dog> unfilteredDogs = getDogsShelter();
    std::vector<Dog> filteredDogs;
    for (const auto& currentDog : unfilteredDogs) {
        if ((currentDog.getBreed() == breed  || breed.empty()) && currentDog.getAge() < age) {
            filteredDogs.push_back(currentDog);
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
    this->indexCurrentDog = (this->indexCurrentDog + 1) % this->getDogsShelter().size();
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
