#include "DynamicArray.h"
#include <stdlib.h>




DynamicArray* create_DynamicArray(int capacity, destructionFunction fct) {
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    if (arr == NULL)
        return NULL;
    arr->capacity = capacity;
    arr->size = 0;
    arr->elems = malloc(capacity * sizeof(TElem));
    if (arr->elems == NULL)
        return NULL;
    arr->destroyFct = fct;

    return arr;
}

void destroy_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; i < arr->size; i++)
        arr->destroyFct(arr->elems[i]);
    free(arr->elems);
    free(arr);
}

void free_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    free(arr->elems);
    free(arr);
}

void resize_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    /*int aux_cap = operationStack->capacity * 2;
    TElem* aux = malloc(aux_cap * sizeof(TElem));
    if (aux == NULL)
        return;
    operationStack->capacity = aux_cap;
    for (int i = 0; i < operationStack->size; i++)
        aux[i] = operationStack->elems[i];
    free(operationStack->elems);
    operationStack->elems = aux;*/
    int aux_cap = arr->capacity * 2;
    TElem* aux = realloc(arr->elems, aux_cap * sizeof(TElem));
    if (aux == NULL)
        return;
    arr->capacity = aux_cap;
    arr->elems = aux;
}

void addElem_DynamicArray(DynamicArray* arr, TElem elem)
{
    if (arr == NULL)
        return;
    if (arr->size == arr->capacity)
        resize_DynamicArray(arr);
    arr->elems[arr->size++] = elem;
}

void removeElem_DynamicArray(DynamicArray* arr, int position)
{
    if (arr == NULL)
        return;
    if (position < 0 || position >= arr->size)
        return;
    arr->destroyFct(arr->elems[position]);
    for (int i = position; i < arr->size - 1; i++)
        arr->elems[i] = arr->elems[i + 1];
    arr->size--;
}

int getSize_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;
    return arr->size;
}

int getCapacity_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;
    return arr->capacity;
}

TElem getAllElems_DynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return NULL;

    return arr->elems;
}

TElem* getElemFromPosition_DynamicArray(DynamicArray* arr, long int position)
{
    if (arr == NULL)
        return NULL;

    return arr->elems[position];
}

void sort_DynamicArray(DynamicArray* arr, compareFunction cmp){
    if (arr == NULL)
        return;
    for (int i = 0; i < arr->size - 1; i++)
        for (int j = i + 1; j < arr->size; j++)
            if (cmp(arr->elems[i], arr->elems[j]) > 0)
            {
                TElem aux = arr->elems[i];
                arr->elems[i] = arr->elems[j];
                arr->elems[j] = aux;
            }
}

/*
void testDynamicArray()
{
    DynamicArray* arr1 = create_DynamicArray(2, (destructionFunction) destroy_Medicine);
    // arr1 - array of planets

    DynamicArray* p1 = create_Medicine("Paracetamol", 200, 10, 10);
    DynamicArray* p2 = create_Medicine("Aspirin", 100, 20, 20);
    DynamicArray* p3 = create_Medicine("Ibuprofen", 300, 30, 30);

    addElem_DynamicArray(arr1, p1);
    addElem_DynamicArray(arr1, p2);
    assert(getSize_DynamicArray(arr1) == 2);
    assert(getCapacity_DynamicArray(arr1) == 2);

    addElem_DynamicArray(arr1, p3);
    assert(getSize_DynamicArray(arr1) == 3);
    assert(getCapacity_DynamicArray(arr1) == 4);

    DynamicArray* arr2 = create_DynamicArray(2, (destructionFunction) destroy_Medicine);
    // arr2 - array of planets
    DynamicArray* p4 = create_Medicine("Panadol", 400, 40, 40);
    addElem_DynamicArray(arr2, p4);

    DynamicArray* arrayOfArrays = create_DynamicArray(2, (destructionFunction) destroy_DynamicArray);
    addElem_DynamicArray(arrayOfArrays, arr1);
    addElem_DynamicArray(arrayOfArrays, arr2);

    destroy_DynamicArray(arrayOfArrays);
}*/
