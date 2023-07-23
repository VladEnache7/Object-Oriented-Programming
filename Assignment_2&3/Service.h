#pragma once

#include "Repository.h"
#include "UndoRedoListOfOperations.h"

typedef struct Service{
    Repository *repository;
    UndoRedoService* undoRedoService;

}Service;


/**
 * Creates an empty service and return a poTInter to it.
 * @param repository a repository
 * @return a poTInter to the service
 */
Service* create_service();

/**
 * Destroys the service and frees up the memory held by it.
 * @param: poTInter to the service(sent as another poTInter(TODO: research about this)) to be deleted
 */
void destroy_service(Service *service);

/**
 * Adds a medicine to the repository
 * @param service: a service
 * @param name: the name of the medicine
 * @param concentration: the concentration of the medicine
 * @param quantity: the quantity of the medicine
 * @param price: the price of the medicine
 * @return 1 if the medicine was added successfully, 0 otherwise
 */
TInt service_add_medicine(Service* service, char* name, TInt concentration, TInt quantity, TInt price);

/**
 * Deletes a medicine from the repository
 * @param service: a service
 * @param name: the name of the medicine
 * @param concentration: the concentration of the medicine
 * @return 1 if the medicine was deleted successfully, 0 otherwise
 */
TInt service_remove_medicine(Service* service, char* name, TInt concentration);

/**
 * Updates a medicine from the repository
 * @param service: a service
 * @param name: the name of the medicine
 * @param concentration: the concentration of the medicine
 * @param new_quantity: the new quantity for the medicine
 * @param new_price: the new price for the medicine
 * @return 1 if the medicine was updated successfully, 0 otherwise
 */
TInt service_update_medicine(Service* service, char* name, TInt concentration, TInt new_quantity, TInt new_price);

/**
 * Returns the medicine list from a repository containing a given string in the name
 * -> sorted ascending by medicine name
 * @param service: a service
 * @param string: a string
 * @return the medicine list from a repository
 */
DynamicArray* service_list_medicines_by_name(Service* service, char* string, TInt* lengthFilteredMedicines);


/**
 * Returns the medicine list from a repository having a quantity less than a given number
 * @param service: a service
 * @param lengthShortSupplyMedicines: the length of the filtered medicine list
 * @param quantity: the quantity to be compared with
 * @return the list of medicines in short supply
 */
DynamicArray* service_list_medicines_in_short_supply(Service* service, TInt* lengthShortSupplyMedicines, TInt quantity);

/*int service_undo(Service *service);

int redo(Service *service);*/

/**
 * Returns the medicine list from a repository
 * @param service: a service
 * @return the medicine list from a repository
 */
DynamicArray* service_get_medicine_list(Service* service);
