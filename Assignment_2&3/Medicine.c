#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Medicine.h"


Medicine* create_Medicine(char *name, TInt concentration, TInt quantity, TInt price) {
    Medicine* medicine = malloc(sizeof(Medicine));
    if (medicine == NULL)
        return NULL;
    medicine->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    if (medicine->name == NULL) {
        free(medicine);
        return NULL;
    }

    strcpy(medicine->name, name);
    medicine->concentration = concentration;
    medicine->quantity = quantity;
    medicine->price = price;
    return medicine;
}

char* get_name(Medicine *self) {
    return self->name;
}

TInt get_concentration(Medicine *self) {
    return self->concentration;
}

TInt get_quantity(Medicine *self) {
    return self->quantity;
}

TInt get_price(Medicine *self) {
    return self->price;
}

void set_quantity(Medicine *self, TInt quantityToBeSet) {
    self->quantity = quantityToBeSet;
}

void set_price(Medicine *self, TInt priceToBeSet) {
    self->price = priceToBeSet;
}

void add_quantity(Medicine *self, TInt quantityToBeAdded) {
    self->quantity += quantityToBeAdded;
}

Medicine* copy_Medicine(Medicine *self) {
    if (self == NULL)
        return NULL;
    Medicine* newMedicine = create_Medicine(self->name, self->concentration, self->quantity, self->price);
    return newMedicine;

}

void destroy_Medicine(Medicine* self) {
    if (self == NULL || self->name == NULL)
        return;
    free(self->name);
    /*// print pointer self
    printf("self: %p \n", self);*/
    free(self);
    self = NULL;
}