#include <iostream>

#include "UserInterface.h"
#include "Exceptions.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"

using namespace std;

UserInterface::UserInterface(ServiceAdmin &serviceAdminToBeSet, ServiceUser &serviceUserToBeSet) : serviceAdmin{
        serviceAdminToBeSet}, serviceUser(serviceUserToBeSet) {}


// the default destructor is used because there are no pointers in the class
UserInterface::~UserInterface() = default;


void UserInterface::run() {
    this->chooseMode();
}


void UserInterface::printStartMenu() {
    cout << "\n---Welcome to “Keep calm and adopt a pet” shelter---" << endl;
    cout << "\t\t1 - Admin Mode" << endl;
    cout << "\t\t2 - User Mode" << endl;
    cout << "\t\tx - Exit" << endl;
    cout << "----------------------------------------------------" << endl;

}


void UserInterface::chooseMode() {
    char choice = '0';
    // while the choice is not x, keep reading commands
    while (choice != 'x') {

        // print the menu
        UserInterface::printStartMenu();

        // read the choice
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': /// admin mode
            {
                this->having10DogsAtStartUp();
                this->startAdminMode();
            }
                break;
            case '2': /// user mode
            {
                this->having10DogsAtStartUp();
                this->startUserMode();
            }
                break;
            case 'x': /// exit
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                break;
        }
    }

}


void UserInterface::printMenuAdmin() {
    cout << "\n----------Admin mode------------" << endl;
    cout << "\t1 - Add a dog" << endl;
    cout << "\t2 - Delete a dog" << endl;
    cout << "\t3 - Update a dog" << endl;
    cout << "\t4 - List all dogs" << endl;
    cout << "\tx - Exit" << endl;
    cout << "--------------------------------" << endl;

}


void UserInterface::startAdminMode() {

    char choice = '0';
    // while the choice is not x, keep reading commands
    while (choice != 'x') {
        // print the menu
        this->printMenuAdmin();

        // read the choice
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': /// add a dog
            {
                string breed, name, photograph;
                int age;
                cout << "Name (names are unique): ";
                cin >> name;
                cout << "Breed: ";
                cin >> breed;
                string stringAge;
                cout << "Age: ";
                cin >> stringAge;
                if (stringAge.find_first_not_of("0123456789") != std::string::npos) {
                    cout << "Age must be a positive number!" << endl;
                    break;
                }
                age = stoi(stringAge);
                cout << "Photograph: ";
                cin >> photograph;
                try {
                    this->serviceAdmin.addDog(name, breed, age, photograph);
                    cout << "Dog added successfully!" << endl;
                } catch (Exception &exception) {
                    cout << exception.what() << endl;
                }

            }
                break;
            case '2': /// delete a dog
            {
                string name;
                cout << "Name of the dog to be deleted (names are unique): ";
                cin >> name;

                try {
                    this->serviceAdmin.deleteDog(name);
                    cout << "Dog deleted successfully!" << endl;
                } catch (Exception &exception) {
                    cout << exception.what() << endl;
                }

            }
                break;
            case '3': /// update a dog
            {
                string newBreed, name, newPhotograph;
                int newAge;

                /// getting the name of the dog to be updated
                cout << "Name of the dog to be updated (Names are unique): ";
                cin >> name;
                if (this->serviceAdmin.getDogPositionByName(name) == -1) {
                    cout << "There is no dog with this name! " << endl;
                    break;
                }

                /// getting the new newBreed from the user
                cout << "New newBreed (if not, write no): ";
                cin >> newBreed;
                if (newBreed == "no")
                    newBreed = this->serviceAdmin.getDogByName(name).getBreed();

                /// getting the new newAge from the user
                string stringNewAge;
                cout << "New Age (if not, write -1): ";
                cin >> stringNewAge;
                if (stringNewAge.find_first_not_of("-0123456789") != std::string::npos) {
                    cout << "Age must be a positive number!" << endl;
                    break;
                }
                newAge = stoi(stringNewAge);
                if (newAge == -1)
                    newAge = this->serviceAdmin.getDogByName(name).getAge();

                /// getting the new newPhotograph from the user
                cout << "New Photograph (if not, write no): ";
                cin >> newPhotograph;
                if (newPhotograph == "no")
                    newPhotograph = this->serviceAdmin.getDogByName(name).getPhotograph();

                try {
                    this->serviceAdmin.updateDog(name, newBreed, newAge, newPhotograph);
                    cout << "Dog updated successfully!" << endl;
                } catch (Exception &exception) {
                    cout << exception.what() << endl;
                }

            }
                break;
            case '4': /// list all dogs
            {
                for (int i = 0; i < this->serviceAdmin.getDogs().getSize(); i++) {
                    cout << "-----> Dog " << i + 1 << " <-----" << endl;
                    cout << "Name: " << this->serviceAdmin.getDogs()[i].getName() << endl;
                    cout << "Breed: " << this->serviceAdmin.getDogs()[i].getBreed() << endl;
                    cout << "Age: " << this->serviceAdmin.getDogs()[i].getAge() << endl;
                    cout << "Photo: " << this->serviceAdmin.getDogs()[i].getPhotograph() << endl << endl;
                }
            }
                break;
            case 'x': /// exit
                goto chooseModeAgain;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                break;

        }
    }
    chooseModeAgain:
    cout << "You have exited the admin mode!" << endl;
}


void UserInterface::printMenuUser() {
    cout << "\n-----------------User-mode-------------------" << endl;
    cout << "\t1 - See the current dog" << endl;
    cout << "\t2 - Adopt the current dog" << endl;
    cout << "\t3 - Go to the next dog" << endl;
    cout << "\t4 - See what dogs you've adopted already" << endl;
    cout << "\t5 - See the dogs of a breed and age < number" << endl;
    cout << "\tx - Exit" << endl;
    cout << "----------------------------------------------" << endl;
}


void UserInterface::printMenuFilteredDogList() {
    cout << "\n----------Filtered Dog List------------" << endl;
    cout << "\t2 - Adopt the current dog" << endl;
    cout << "\t3 - Go to the next dog" << endl;
    cout << "\t4 - See what dogs you've adopted already" << endl;
    cout << "\tx - Exit this functionality" << endl;
    cout << "----------------------------------------" << endl;
}


void UserInterface::startUserMode() {


    char choice = '0';
    // while the choice is not x, keep reading commands
    while (choice != 'x') {
        // print the menu
        this->printMenuUser();

        // read the choice
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': /// see the dogs one by one
            {
                if (this->serviceUser.getDogsShelter().getSize() == 0) {
                    cout << "There are no dogs left in our shelter!" << endl;
                    break;
                }
                // get the current dog
                Dog currentDog = this->serviceUser.getCurrentDog();

                // print the current dog
                cout << "----Current Dog---- " << endl;
                cout << "Name: " << currentDog.getName() << endl;
                cout << "Breed: " << currentDog.getBreed() << endl;
                cout << "Age: " << currentDog.getAge() << endl;
                cout << "Photo: " << currentDog.getPhotograph() << endl << endl;
            }
                break;
            case '2': /// adopt the current dog
            {
                if (this->serviceUser.getDogsShelter().getSize() == 0) {
                    cout << "There are no dogs left in our shelter!" << endl;
                    break;
                }
                this->serviceUser.adoptDog(this->serviceUser.getCurrentDog());
                cout << "Dog adopted successfully!" << endl;
            }
                break;
            case '3': /// go to the next dog
            {
                if (this->serviceUser.getDogsShelter().getSize() == 0) {
                    cout << "There are no dogs left in our shelter!" << endl;
                    break;
                }
                this->serviceUser.goToTheNextDog();
            }
                break;
            case '4': /// see what dogs you've adopted already
            {
                if (this->serviceUser.getDogsAdopted().getSize() == 0) {
                    cout << "You haven't adopted any dogs yet!" << endl;
                    break;
                }
                cout << "---You've adopted the following dogs: ---" << endl;
                for (int i = 0; i < this->serviceUser.getDogsAdopted().getSize(); i++) {
                    cout << "-----> Dog " << i + 1 << "<-----" << endl;
                    cout << "Name: " << this->serviceUser.getDogsAdopted()[i].getName() << endl;
                    cout << "Breed: " << this->serviceUser.getDogsAdopted()[i].getBreed() << endl;
                    cout << "Age: " << this->serviceUser.getDogsAdopted()[i].getAge() << endl;
                    cout << "Photo: " << this->serviceUser.getDogsAdopted()[i].getPhotograph() << endl << endl;
                }
            }
                break;
            case '5': /// see the dogs of a breed and age < number
            {
                string breed;
                int age;
                cout << "Breed (if not, write 'no'): ";
                cin >> breed;
                if (breed == "no")
                    breed = "";
                string stringAge;
                cout << "Age: ";
                cin >> stringAge;
                if (stringAge.find_first_not_of("0123456789") != std::string::npos) {
                    cout << "Age must be a positive number!" << endl;
                    break;
                }
                age = stoi(stringAge);
                DynamicVector<Dog> filteredDogs = this->serviceUser.getDogsFiltered(breed, age);
                if (filteredDogs.getSize() == 0) {
                    cout << "There are no Dogs with this breed and younger than " << age << endl;
                    break;
                }
                int index = 0;
                while (index < filteredDogs.getSize()) {
                    cout << "-----> Dog " << index + 1 << " <-----" << endl;
                    cout << "Name: " << filteredDogs[index].getName() << endl;
                    cout << "Breed: " << filteredDogs[index].getBreed() << endl;
                    cout << "Age: " << filteredDogs[index].getAge() << endl;
                    cout << "Photo: " << filteredDogs[index].getPhotograph() << endl << endl;
                    printMenuFilteredDogList();
                    char choice2 = '0';
                    while (choice2 != 'x') {
                        cout << "Your choice: ";
                        cin >> choice2;
                        switch (choice2) {
                            case '2': /// adopt the current dog
                            {
                                if (this->serviceUser.getDogsShelter().getSize() == 0) {
                                    cout << "There are no dogs left in our shelter!" << endl;
                                    break;
                                }
                                Dog currentDog = filteredDogs[index];
                                this->serviceUser.adoptDog(currentDog.getName());
                                filteredDogs.removeCertainElement(currentDog);
                                cout << "Dog adopted successfully!" << endl;
                                if (filteredDogs.getSize() == 0) {
                                    cout << "There are no more dogs left!" << endl;
                                    goto outOfThisFunctionality;
                                }
                                index = (index + 1) % filteredDogs.getSize();
                                choice2 = 'x';
                            }
                                break;
                            case '3': /// go to the next dog
                                index = (index + 1) % filteredDogs.getSize();
                                choice2 = 'x';
                                break;
                            case '4': /// see what dogs you've adopted already
                            {
                                if (this->serviceUser.getDogsAdopted().getSize() == 0) {
                                    cout << "You haven't adopted any dogs yet!" << endl;
                                    break;
                                }
                                cout << "---You've adopted the following dogs: ---" << endl;
                                for (int i = 0; i < this->serviceUser.getDogsAdopted().getSize(); i++) {
                                    cout << "Dog " << i + 1 << ":" << endl;
                                    cout << "Name: " << this->serviceUser.getDogsAdopted()[i].getName() << endl;
                                    cout << "Breed: " << this->serviceUser.getDogsAdopted()[i].getBreed() << endl;
                                    cout << "Age: " << this->serviceUser.getDogsAdopted()[i].getAge() << endl;
                                    cout << "Photo: " << this->serviceUser.getDogsAdopted()[i].getPhotograph() << endl
                                         << endl;
                                    cout << "\t-------------------------" << endl;
                                }
                                cout << "-----------------------------------------" << endl;
                            }
                                break;
                            case 'x':
                                goto outOfThisFunctionality;
                            default:
                                cout << "Invalid choice! Please try again!" << endl;
                                break;
                        }
                    }
                }

            }
                outOfThisFunctionality:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                break;
        }
    }
    cout << "Thank you for using our application!" << endl;
}


void UserInterface::having10DogsAtStartUp(){
    // having 10 dogs in the repository
    if(this->serviceAdmin.getDogs().getSize() == 0)
    {
        this->serviceAdmin.addDog("Rex", "Labrador Retriever", 3,
                                  "https://ro.wikipedia.org/wiki/Labrador_Retriever#/media/Fi%C8%99ier:YellowLabradorLooking.jpg");
        this->serviceAdmin.addDog("Bella", "German Shepherd", 6,
                                  "https://en.wikipedia.org/wiki/File:German_Shepherd_-_DSC_0346_(10096362833).jpg");
        this->serviceAdmin.addDog("Max", "Golden Retriever", 2,
                                  "https://en.wikipedia.org/wiki/File:Golden_Retriever_Carlos_%2810581910556%29.jpg");
        this->serviceAdmin.addDog("Charlie", "Bulldog", 4, "https://en.wikipedia.org/wiki/File:English_Bulldog.jpg");
        this->serviceAdmin.addDog("Lucy", "Beagle", 1, "https://en.wikipedia.org/wiki/File:Beagle.jpg");
        this->serviceAdmin.addDog("Molly", "Poodle", 5, "https://en.wikipedia.org/wiki/File:Toy_Poodle.jpg");
        this->serviceAdmin.addDog("Daisy", "Chihuahua", 3,
                                  "https://en.wikipedia.org/wiki/File:Chihuahua_(4479047538).jpg");
        this->serviceAdmin.addDog("Rocky", "Pug", 2, "https://en.wikipedia.org/wiki/File:Pug_dog.jpg");
        this->serviceAdmin.addDog("Buddy", "Boxer", 4, "https://en.wikipedia.org/wiki/File:Boxer_(dog).jpg");
        this->serviceAdmin.addDog("Maggie", "Siberian Husky", 1,
                                  "https://en.wikipedia.org/wiki/File:Siberian_Husky.jpg");
    }
}





