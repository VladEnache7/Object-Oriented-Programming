#include "Tests.h"
#include "Service.h"
#include "DynamicArray.h"
#include <assert.h>
#include <malloc.h>

void service_add_medicine_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);
    assert(service_add_medicine(service, name, concentration, quantity, price) == 0);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);

    // destroy the service
    destroy_service(service);
}

void service_remove_medicine_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);
    assert(service_remove_medicine(service, name, concentration) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);
    assert(service_remove_medicine(service, name, concentration) == 0);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);

    // destroy the service
    destroy_service(service);
}

void service_update_medicine_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);
    assert(service_update_medicine(service, name, concentration, 20, 20) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);
    assert(service_update_medicine(service, "Aspirin", concentration, 20, 20) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);
    assert(service_update_medicine(service, "Aspirin", concentration, 20, 20) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);
    assert(service_update_medicine(service, "Aspirin", concentration, 20, 20) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);

    // destroy the service
    destroy_service(service);
}

void service_get_medicine_list_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);

    // destroy the service
    destroy_service(service);
}

void service_list_medicines_by_name_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Paracetamol", concentration + 100, quantity, price) == 1);
    TInt length = 0;
    DynamicArray *filteredMedicines = service_list_medicines_by_name(service, name, &length);
    assert(getSize_DynamicArray(filteredMedicines) == 2);

    // free the memory
    free_DynamicArray(filteredMedicines);

    // destroy the service
    destroy_service(service);
}

void service_list_medicines_in_short_supply_test() {
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Paracetamol", concentration + 100, quantity, price) == 1);
    TInt length = 0;
    DynamicArray *shortSupplyMedicines = service_list_medicines_in_short_supply(service, &length, 50);
    assert(getSize_DynamicArray(shortSupplyMedicines) == 3);

    // free the memory
    free_DynamicArray(shortSupplyMedicines);

    // destroy the service
    destroy_service(service);
}

void undo_test(){
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    undo(service);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);

    // destroy the service
    destroy_service(service);
}

void redo_test(){
    Service* service = create_service();
    char* name = "Paracetamol";
    TInt concentration = 500;
    TInt quantity = 10;
    TInt price = 10;
    assert(service_add_medicine(service, name, concentration, quantity, price) == 1);
    assert(service_add_medicine(service, "Aspirin", concentration, quantity, price) == 1);
    undo(service);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 1);
    redo(service);
    assert(getSize_DynamicArray(service_get_medicine_list(service)) == 2);

    // destroy the service
    destroy_service(service);
}

void test_all() {
    service_add_medicine_test();
    service_remove_medicine_test();
    service_update_medicine_test();
    service_get_medicine_list_test();
    service_list_medicines_by_name_test();
    service_list_medicines_in_short_supply_test();
    undo_test();
    redo_test();
}


