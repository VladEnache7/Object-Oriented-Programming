#pragma once

#include "ServiceAdmin.h"
#include "ServiceUser.h"

class UserInterface {
private:
    // the service for the admin
    ServiceAdmin& serviceAdmin;


    // the service for the user
    ServiceUser& serviceUser;

public:
    UserInterface(ServiceAdmin& serviceAdminToBeSet, ServiceUser& serviceUserToBeSet);
    ~UserInterface();

    // run the application
    void run();
    void chooseMode();
    static void printStartMenu();

    // admin mode
    void startAdminMode();
    static void printMenuAdmin();

    // user mode
    void startUserMode();
    static void printMenuUser();

    static void printMenuFilteredDogList();

    void having10DogsAtStartUp();
};

