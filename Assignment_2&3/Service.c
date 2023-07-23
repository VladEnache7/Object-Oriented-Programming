#include <stdlib.h>
#include <string.h>
#include "Service.h"
#include "Medicine.h"


Service* create_service(){
    Service* service = (Service*)malloc(sizeof(Service));

    // setting up the repository
    Repository* repository = create_repository(20);
    service->repository = repository;

    // setting up the undoRedoService
    UndoRedoService* undoRedoService = create_undoRedoService();
    service->undoRedoService = undoRedoService;

    //returning the created service
    return service;
}

void destroy_service(Service *service){
    // freeing the repository
    destroy_repository(service->repository);

    // freeing the undoRedoService
    destroy_undoRedoService(service->undoRedoService);
    free(service);
    service = NULL;
}

DynamicArray* service_get_medicine_list(Service* service){
    return repo_get_medicine_list(service->repository);
}

TInt service_add_medicine(Service* service, char* name, TInt concentration, TInt quantity, TInt price){
    if (has_medicine(service->repository, name, concentration) != -1) {
        add_medicine(service->repository, name, concentration, quantity, price);
        return 0;
    }
    service->repository = add_medicine(service->repository, name, concentration, quantity, price);

    // for undo-redo functionalities
    Medicine* medicine_undoRedo = return_medicine(service->repository, name, concentration);
    Operation* operation = createOperation((undoRedoFct) remove_medicine, (undoRedoFct) add_medicine, medicine_undoRedo,
                                           medicine_undoRedo);
    push_undoRedoService(service->undoRedoService, operation);
    return 1;
}

TInt service_remove_medicine(Service* service, char* name, TInt concentration){
    // for undo-redo functionalities
    Medicine* medicine_undoRedo = return_medicine(service->repository, name, concentration);
    Operation* operation = createOperation((undoRedoFct) add_medicine, (undoRedoFct) remove_medicine, medicine_undoRedo,
                                           medicine_undoRedo);
    push_undoRedoService(service->undoRedoService, operation);

    if (has_medicine(service->repository, name, concentration) == -1)
        return 0;
    remove_medicine(service->repository, name, concentration, 0, 0);


    return 1;
}

TInt service_update_medicine(Service* service, char* name, TInt concentration, TInt new_quantity, TInt new_price){
    // medicine before update
    Medicine* medicine_undo = return_medicine(service->repository, name, concentration);

    if (has_medicine(service->repository, name, concentration) == -1)
        return 0;
    update_medicine(service->repository, name, concentration, new_quantity, new_price);

    // medicine after update
    Medicine* medicine_redo = return_medicine(service->repository, name, concentration);
    Operation* operation = createOperation((undoRedoFct) update_medicine, (undoRedoFct) update_medicine, medicine_undo,
                                           medicine_redo);
    push_undoRedoService(service->undoRedoService, operation);
    return 1;
}

int compareMedicineByNameAscending(Medicine* medicine1, Medicine* medicine2){
    return strcmp(get_name(medicine1), get_name(medicine2));
}

DynamicArray* service_list_medicines_by_name(Service* service, char* string, TInt* lengthFilteredMedicines){
    DynamicArray *medicine_list = repo_get_medicine_list(service->repository);
    TInt length = get_length(service->repository);

    for (TInt i = 0; i < length; ++i) {
        if (strstr(get_name((Medicine *) getElemFromPosition_DynamicArray(medicine_list, i)), string) != NULL) {
            (*lengthFilteredMedicines)++;
        }
    }
    DynamicArray* filtered_list = create_DynamicArray((int)(*lengthFilteredMedicines),
                                                      (destructionFunction) destroy_Medicine);
    for (TInt i = 0; i < length; ++i) {
        if (strstr(get_name((Medicine *) getElemFromPosition_DynamicArray(medicine_list, i)), string) != NULL) {
            addElem_DynamicArray(filtered_list, getElemFromPosition_DynamicArray(medicine_list, i));
        }
    }

    // sorted ascending by medicine name
    sort_DynamicArray(filtered_list, (compareFunction) compareMedicineByNameAscending);
    return filtered_list;
}

DynamicArray* service_list_medicines_in_short_supply(Service* service, TInt* lengthShortSupplyMedicines, TInt quantity){
    DynamicArray *medicine_list = repo_get_medicine_list(service->repository);
    TInt length = get_length(service->repository);

    for (TInt i = 0; i < length; ++i) {
        if (get_quantity((Medicine *) getElemFromPosition_DynamicArray(medicine_list, i)) < quantity) {
            (*lengthShortSupplyMedicines)++;
        }
    }
    DynamicArray* short_supply_list = create_DynamicArray((int)(*lengthShortSupplyMedicines),
                                                          (destructionFunction) destroy_Medicine);


    for (TInt i = 0; i < length; ++i) {
        if (get_quantity((Medicine *) getElemFromPosition_DynamicArray(medicine_list, i)) < quantity) {
            addElem_DynamicArray(short_supply_list, getElemFromPosition_DynamicArray(medicine_list, i));
        }
    }
    return short_supply_list;
}
