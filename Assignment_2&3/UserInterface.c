#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "UserInterface.h"

UserInterface *create_user_interface() {
    Service *service = create_service();
    UserInterface *user_interface = (UserInterface *) malloc(sizeof(UserInterface));
    user_interface->service = service;
    return user_interface;
}

void print_menu() {
    printf("1 - Add a medicine\n");
    printf("2 - Remove a medicine\n");
    printf("3 - Update a medicine\n");
    printf("4 - See all available medicines containing a given string (type 'all' to list all medicines)\n");
    printf("5 - See only those medicines that are in short supply\n");
    printf("6 - Undo the last operation\n");
    printf("7 - Redo the last operation\n");
    printf("x - Exit\n");
}

void start_user_interface(UserInterface *user_interface) {
    //having 10 hardcoded medicines at the start-up
    {
        service_add_medicine(user_interface->service, "Paracetamol", 500, 10, 10);
        service_add_medicine(user_interface->service, "Paracetamol", 200, 20, 8);
        service_add_medicine(user_interface->service, "Antibiotics", 300, 30, 50);
        service_add_medicine(user_interface->service, "Ibuprofen", 400, 10, 20);
        service_add_medicine(user_interface->service, "Aspirin", 500, 30, 10);
        service_add_medicine(user_interface->service, "Naproxen", 600, 20, 30);
        service_add_medicine(user_interface->service, "Diclofenac", 700, 50, 40);
        service_add_medicine(user_interface->service, "Acetaminophen", 800, 70, 50);
        service_add_medicine(user_interface->service, "Vitamin D", 900, 80, 60);
        service_add_medicine(user_interface->service, "Vitamin C", 1000, 90, 70);
        service_add_medicine(user_interface->service, "Vitamin B12", 1100, 10, 80);
        service_add_medicine(user_interface->service, "Vitamin B6", 1200, 40, 90);
    }
    char choice = '0';
    print_menu();
    while (choice != 'x') {
        printf("Enter your choice: ");
        //getting the choice
        scanf("%c", &choice);

        switch (choice) {
            case '1': // add a medicine
            {
                // getting the name
                char name[50], *ptr = NULL;
                printf("Name:");
                scanf("%s", name);

                TInt concentration, quantity, price;
                // getting the concentration, quantity and price
                {
                    char concentrationStr[20], quantityStr[20], priceStr[20];

                    // getting the concentration
                    {
                        printf("Concentration:");
                        scanf("%s", concentrationStr);
                        concentration = strtol(concentrationStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (concentration == LONG_MAX || concentration == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (concentration == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }

                    // getting the quantity
                    {
                        printf("Quantity:");
                        scanf("%s", quantityStr);
                        quantity = strtol(quantityStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (quantity == LONG_MAX || quantity == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (quantity == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }

                    // getting the price
                    {
                        printf("Price:");
                        scanf("%s", priceStr);
                        price = strtol(priceStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (price == LONG_MAX || price == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (price == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }
                }

                if (service_add_medicine(user_interface->service, name, concentration, quantity, price) == 0)
                    printf("-> Because the medicine already exists the quantity was added\n");
                else
                    printf("-> Medicine added successfully!\n");

            }
                getchar();
                break;
            case '2': // remove a medicine
            {
                // getting the name
                char name[50], *ptr = NULL;
                printf("Name:");
                scanf("%s", name);

                TInt concentration;
                // getting the concentration
                {
                    char concentrationStr[20];
                    printf("Concentration:");
                    scanf("%s", concentrationStr);
                    concentration = strtol(concentrationStr, (char **) ptr, 10);
                    // this block is for the input validation
                    {
                        if (concentration == LONG_MAX || concentration == LONG_MIN) {
                            perror("!! Problem is -> ");
                            continue;
                        } else if (concentration == 0) {
                            printf("No number found input is -> %s\n", ptr);
                            continue;
                        }
                    }
                }

                if (service_remove_medicine(user_interface->service, name, concentration) == 0)
                    printf("-> Medicine not found!\n");
                else
                    printf("-> Medicine removed successfully!\n");

            }
                getchar();
                break;
            case '3': // Update a medicine
            {
                // getting the name
                char name[50];
                printf("Name:");
                scanf("%s", name);

                TInt concentration, new_quantity, new_price;
                // getting the concentration, new_quantity and new_price
                {
                    char concentrationStr[20], new_quantityStr[20], new_priceStr[20];
                    char *ptr = NULL;
                    // getting the concentration
                    {
                        printf("Concentration:");
                        scanf("%s", concentrationStr);
                        concentration = strtol(concentrationStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (concentration == LONG_MAX || concentration == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (concentration == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }

                    // getting the new_quantity
                    {
                        printf("New quantity:");
                        scanf("%s", new_quantityStr);
                        new_quantity = strtol(new_quantityStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (new_quantity == LONG_MAX || new_quantity == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (new_quantity == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }

                    // getting the new_price
                    {
                        printf("New price:");
                        scanf("%s", new_priceStr);
                        new_price = strtol(new_priceStr, (char **) ptr, 10);
                        // this block is for the input validation
                        {
                            if (new_price == LONG_MAX || new_price == LONG_MIN) {
                                perror("!! Problem is -> ");
                                continue;
                            } else if (new_price == 0) {
                                printf("No number found input is -> %s\n", ptr);
                                continue;
                            }
                        }
                    }
                }

                if (service_update_medicine(user_interface->service, name, concentration, new_quantity,
                                            new_price) == 0)
                    printf("-> Medicine not found!\n");
                else
                    printf("-> Medicine updated successfully!\n");

            }
                getchar();
                break;
            case '4': // See all available medicines containing a given string (type 'all' to list all medicines)
            {
                char str[50];
                printf("Enter the string: ");
                scanf("%s", str);
                // if the user typed all make the string empty to list all the medicines
                if (strcmp(str, "all") == 0)
                    strcpy(str, "");
                TInt lengthFilteredMedicines = 0;
                DynamicArray *filteredMedicines = service_list_medicines_by_name(user_interface->service, str,
                                                                                 &lengthFilteredMedicines);

                if(lengthFilteredMedicines == 0){
                    printf("-> No medicine found out this name in it!\n");
                    getchar();
                    break;
                }

                //print the filtered medicines
                for (TInt i = 0; i < lengthFilteredMedicines; i++)
                    printf("%s %ld %ld %ld\n", get_name(
                                   (Medicine *) getElemFromPosition_DynamicArray(filteredMedicines, i)),
                           get_concentration((Medicine *) getElemFromPosition_DynamicArray(filteredMedicines, i)),
                           get_quantity((Medicine *) getElemFromPosition_DynamicArray(filteredMedicines, i)), get_price(
                                    (Medicine *) getElemFromPosition_DynamicArray(filteredMedicines, i)));
                // free the memory
                // here I just free the pointer because I do not want to free the medicines
                free_DynamicArray(filteredMedicines);
            }
                getchar();
                break;
            case '5': // See only those medicines that are in short supply
            {
                //getting the quantity
                TInt quantity;
                {
                    char numberOfItemsStr[20], *ptr = NULL;
                    printf("Quantity to be compared with:");
                    scanf("%s", numberOfItemsStr);
                    quantity = strtol(numberOfItemsStr, (char **) ptr, 10);
                    // this block is for the input validation
                    {
                        if (quantity == LONG_MAX || quantity == LONG_MIN) {
                            perror("!! Problem is -> ");
                            continue;
                        } else if (quantity == 0) {
                            printf("No number found, input is -> %s \n", ptr);
                            continue;
                        }
                    }
                }

                TInt lengthShortSupplyMedicines = 0;
                DynamicArray *shortSupplyMedicines = service_list_medicines_in_short_supply(user_interface->service, &lengthShortSupplyMedicines, quantity);

                if(lengthShortSupplyMedicines == 0){
                    printf("-> There are no medicine in short supply!\n");
                    getchar();
                    break;
                }
                //print the medicines in short supply
                for (TInt i = 0; i < lengthShortSupplyMedicines; i++)
                    printf("%s %ld %ld %ld \n", get_name(
                                   (Medicine *) getElemFromPosition_DynamicArray(shortSupplyMedicines, i)),
                           get_concentration((Medicine *) getElemFromPosition_DynamicArray(shortSupplyMedicines, i)),
                           get_quantity((Medicine *) getElemFromPosition_DynamicArray(shortSupplyMedicines, i)), get_price(
                                    (Medicine *) getElemFromPosition_DynamicArray(shortSupplyMedicines, i)));

                // free the memory
                free_DynamicArray(shortSupplyMedicines);
            }
                getchar();
                break;
            case '6': // undo the last operation
            {
                if (undo(user_interface->service) == 0)
                    printf("-> No more operations to undo!\n");
                else
                    printf("-> Undo successfully!\n");
            }
                getchar();
                break;
            case '7': // redo the last operation
            {
                if (redo(user_interface->service) == 0)
                    printf("-> No more operations to redo!\n");
                else
                    printf("-> Redo successfully!\n");
            }
                getchar();
                break;
            case 'x':
                printf("Goodbye!\n");
                getchar();
                break;
            default:
                printf("Invalid choice!\n");
                getchar();
                break;

        }
    }

}

void destroy_user_interface(UserInterface *user_interface) {
    destroy_service(user_interface->service);
    free(user_interface);
}