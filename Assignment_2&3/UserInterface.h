#pragma once
#include "Service.h"

typedef struct UserInterface{
    Service *service;
}UserInterface;

/**
 * Creates an empty user interface and return a pointer to it.
 * @param service a service
 * @return a pointer to the user interface
 */
UserInterface* create_user_interface();

/**
 * Destroys the user interface and frees up the memory held by it.
 * @param: pointer to the user interface(sent as another pointer(TODO: research about this)) to be deleted
 */
void destroy_user_interface(UserInterface *user_interface);

/**
 * Starts the user interface
 * @param user_interface: a user interface
 */
void start_user_interface(UserInterface* user_interface);

/**
 * Prints the menu
 */

void print_menu();