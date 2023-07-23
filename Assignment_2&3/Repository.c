#include <stdlib.h>
#include <string.h>
#include "Repository.h"

Repository* create_repository(TInt capacity){
    Repository* repository = (Repository*)malloc(sizeof(Repository));
    repository->medicine_list = create_DynamicArray((int) capacity, (destructionFunction) destroy_Medicine);
    /*repository->length = 0;
    repository->capacity = capacity;*/
    return repository;
}

DynamicArray* repo_get_medicine_list(Repository* repository){
    return repository->medicine_list;
}

/*void set_medicine_list(Repository* repository, Medicine* new_medicine_list){
    repository->medicine_list = new_medicine_list;
}*/

TInt get_length(Repository* repository){
    return getSize_DynamicArray(repository->medicine_list);
}

/*void set_length(Repository* repository, TInt new_length){
    repository->length = new_length;
}*/


//TODO - I should use this one
void destroy_repository(Repository *repository){
    /*for (TInt i = 0; i < (*repository)->length; ++i) {
        Medicine* medicine_list = (*repository)->medicine_list;
        destroy_Medicine(&medicine_list[i]);
    }
    free((*repository)->medicine_list);*/
    destroy_DynamicArray(repository->medicine_list);
    free(repository);
    repository = NULL;
}

TInt has_medicine(Repository *repository, char* name, TInt concentration){
    for(TInt i = 0; i < get_length(repository); i++){
        if(strcmp(get_name((Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, i)), name) == 0 && get_concentration(
                (Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, i)) == concentration){
            return i;
        }
    }
    return -1;
}

Medicine* return_medicine(Repository *repository, char* name, TInt concentration){
    TInt indexMedicine = has_medicine(repository, name, concentration);
    if (indexMedicine == -1)
        return NULL;
    return (Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, indexMedicine);
}

/*Repository* resize_repository(Repository* repository){
    TInt auxCapacity = repository->capacity * 2;
    TInt auxLength = repository->length;
    repository->medicine_list = realloc(repository->medicine_list, auxCapacity * sizeof(Medicine));
//    newRepository->length = repository->length;
    repository->capacity = auxCapacity;
    repository->length = auxLength;
    return repository;
}*/

Repository* add_medicine(Repository *repository, char* name, TInt concentration, TInt quantity, TInt price){
    TInt indexMedicine = has_medicine(repository, name, concentration);
    /*if(repository->length == repository->capacity)
        repository = resize_repository(repository);*/

    //If a product that already exists is added, its quantity will be updated (the new quantity is added to the existing one)
    if(indexMedicine != -1){
        add_quantity((Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, indexMedicine), quantity);
    }
    else{
        Medicine* medicine = create_Medicine(name, concentration, quantity, price);
        addElem_DynamicArray(repository->medicine_list, medicine);
    }
    return repository;
}

void remove_medicine(Repository *repository, char* name, TInt concentration, __attribute__((unused)) TInt quantity, __attribute__((unused)) TInt price){
    TInt indexMedicine = has_medicine(repository, name, concentration);
//    Medicine* medicine = getElemFromPosition_DynamicArray(repository->medicine_list, indexMedicine);
    if(indexMedicine == -1)
        return;
    removeElem_DynamicArray(repository->medicine_list, (int) indexMedicine);
    /*for(TInt i = indexMedicine; i < repository->length - 1; i++){
        repository->medicine_list[i] = repository->medicine_list[i + 1];
    }
    repository->length--;*/
}

void update_medicine(Repository *repository, char* name, TInt concentration, TInt newQuantity, TInt newPrice){
    TInt indexMedicine = has_medicine(repository, name, concentration);
    if(indexMedicine == -1)
        return;
    set_quantity((Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, indexMedicine), newQuantity);
    set_price((Medicine *) getElemFromPosition_DynamicArray(repository->medicine_list, indexMedicine), newPrice);
}

