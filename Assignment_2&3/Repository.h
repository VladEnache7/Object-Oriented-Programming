#pragma once

#include "Medicine.h"
#include "DynamicArray.h"

typedef struct Repository{
    DynamicArray* medicine_list;
}Repository;

/**
* Creates a repository with capacity given and return a poTInter to it.
*/
Repository* create_repository(TInt capacity);

/**
 * Resizes the repository by doubling its capacity
 * @return a new repository with the capacity doubled
 */
Repository* resize_repository();

/**
 * Returns a poTInter toward an array of medicine from a repository
 * @param repository: a repository
 * @return a poTInter toward an array of medicine from a repository
 */
DynamicArray* repo_get_medicine_list(Repository* repository);

/**
 * Sets the poTInter of medicine list from a repository to a new list of medicines
 * @param repository: a repositort
 * @param new_medicine_list: the new list of medicines
 */
void set_medicine_list(Repository* repository, Medicine* new_medicine_list);

/**
 * Returns the length of the medicine list from a repository
 * @param repository: a repository
 * @return the length of the medicine list from a repository
 */
TInt get_length(Repository* repository);

/**
 * Sets the length of the medicine list from a repository to a new value
 * @param repository: a repository
 * @param new_length: the new length of the medicine list
 */
void set_length(Repository* repository, TInt new_length);

/**
 * Destroys the repository and frees up the memory held by it.
 * @param: poTInter to the repository(sent as another poTInter(TODO: research about this)) to be deleted
 */
void destroy_repository(Repository *repository);

/**
 * Checks if a medicine is already in a repository
 * @return non-negative index if search was successful, -1 otherwise
 */
TInt has_medicine(Repository *repository, char* name, TInt concentration);

/**
 * Returns the medicine if name exists and has the concentration, otherwise an invalid gear with concentration = -1
 */
Medicine* return_medicine(Repository *repository, char* name, TInt concentration);

/**
 * Adds a medicine to the repository
 * @param repository a repository
 * @param name the name of the medicine
 * @param concentration the concentration of the medicine
 * @param quantity the quantity of the medicine
 * @param price the price of the medicine
 */
Repository* add_medicine(Repository *repository, char* name, TInt concentration, TInt quantity, TInt price);

/**
 * Removes a medicine from the repository
 * @param name: name of the medicine to be removed
 * @param concentration: concentration of the medicine to be removed
 */
void remove_medicine(Repository *repository, char* name, TInt concentration, __attribute__((unused)) TInt quantity, TInt price);


/**
 * Updates a medicine from the repository
 * @param repository: a repository
 * @param name: name of the medicine to be updated
 * @param concentration: concentration of the medicine to be updated
 * @param newQuantity: the new quantity of the medicine
 * @param newPrice: the new price of the medicine
 */
void update_medicine(Repository *repository, char* name, TInt concentration, TInt newQuantity, TInt newPrice);

