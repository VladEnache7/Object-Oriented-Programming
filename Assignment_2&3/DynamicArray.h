
#pragma once
//#include "DynamicArray.h"
//#include "UndoRedoListOfOperations.h"

typedef void* TElem;

typedef void (*destructionFunction)(TElem);

typedef struct DynamicArray
{
    TElem* elems;
    int capacity, size;

    destructionFunction destroyFct;
} DynamicArray;

DynamicArray* create_DynamicArray(int capacity, destructionFunction fct);
void destroy_DynamicArray(DynamicArray* arr);
void addElem_DynamicArray(DynamicArray* arr, TElem elem);
void removeElem_DynamicArray(DynamicArray* arr, int position);

void free_DynamicArray(DynamicArray* arr);

// getters
int getSize_DynamicArray(DynamicArray* arr);
int getCapacity_DynamicArray(DynamicArray* arr);
TElem getAllElems_DynamicArray(DynamicArray* arr);
TElem* getElemFromPosition_DynamicArray(DynamicArray* arr, long int position);

typedef int (*compareFunction)(TElem, TElem);
void sort_DynamicArray(DynamicArray* arr, compareFunction cmp);

void testDynamicArray();