#pragma once

typedef long int TInt;

typedef struct Medicine{
    char *name;
    TInt concentration, quantity, price;
}Medicine;

//create_Medicine a new medicine
Medicine* create_Medicine(char* name, TInt concentration, TInt quantity, TInt price);

//get the attributes of a medicine
char* get_name(Medicine* self);
TInt get_concentration(Medicine* self);
TInt get_quantity(Medicine* self);
TInt get_price(Medicine* self);

//set the attributes of a medicine
void set_quantity(Medicine* self, TInt quantityToBeSet);
void set_price(Medicine* self, TInt priceToBeSet);

//other functions
void add_quantity(Medicine* self, TInt quantityToBeAdded);
Medicine* copy_Medicine(Medicine* self);

//destroy_Medicine a medicine
void destroy_Medicine(Medicine* self);

