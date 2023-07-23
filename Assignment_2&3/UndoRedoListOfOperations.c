#include <stdlib.h>
#include "UndoRedoListOfOperations.h"
#include "Service.h"
//#include "DynamicArray.h"
//--------------------Operation------------------------
Operation *createOperation(undoRedoFct undo, undoRedoFct redo, Medicine *medicineToUndo, Medicine *medicineToRedo)
{
    Operation* operation = malloc(sizeof(Operation));
    if (operation == NULL)
        return NULL;
    operation->medicineToUndo = copy_Medicine(medicineToUndo);
    operation->medicineToRedo = copy_Medicine(medicineToRedo);
    operation->undoFunction = undo;
    operation->redoFunction = redo;
    return operation;
}

void destroyOperation(Operation* operation)
{
    if (operation == NULL)
        return;
    destroy_Medicine(operation->medicineToUndo);
    destroy_Medicine(operation->medicineToRedo);
    free(operation);
}

//--------------------UndoRedoService------------------------

UndoRedoService *create_undoRedoService() {
    UndoRedoService *s = NULL;
    s = malloc(sizeof(UndoRedoService));
    if (s == NULL)
        return s;
    s->operationStack = create_DynamicArray(20, (destructionFunction) destroyOperation);
    return s;
}

void destroy_undoRedoService(UndoRedoService *service) {
    if (service == NULL)
        return;
    destroy_DynamicArray(service->operationStack);
    free(service);
}

void push_undoRedoService(UndoRedoService *s, Operation *operation) {
    if (s == NULL)
        return;
    // delete the elements after the current index
    while (getSize_DynamicArray(s->operationStack) > s->index)
        removeElem_DynamicArray(s->operationStack, getSize_DynamicArray(s->operationStack) - 1);
    s->index++;
    addElem_DynamicArray(s->operationStack, operation);
}

int isEmpty(UndoRedoService *s) {
    if (s == NULL)
        return 1;
    return (getSize_DynamicArray(s->operationStack) == 0);
}

int undo(Service *service){
    if (service == NULL)
        return 0;
    if (isEmpty(service->undoRedoService))
        return 0;
    Operation* operation = (Operation *) getElemFromPosition_DynamicArray(service->undoRedoService->operationStack,
                                                                          service->undoRedoService->index - 1);
    operation->undoFunction(service->repository, get_name(operation->medicineToUndo), get_concentration(operation->medicineToUndo), get_quantity(operation->medicineToUndo), get_price(operation->medicineToUndo));
    service->undoRedoService->index--;
    return 1;
}

int redo(Service *service){
    if (service == NULL)
        return 0;
    if (service->undoRedoService->index == getSize_DynamicArray(service->undoRedoService->operationStack))
        return 0;
    Operation* operation = (Operation *) getElemFromPosition_DynamicArray(service->undoRedoService->operationStack,
                                                                          service->undoRedoService->index);
    operation->redoFunction(service->repository, get_name(operation->medicineToRedo), get_concentration(operation->medicineToRedo), get_quantity(operation->medicineToRedo), get_price(operation->medicineToRedo));
    service->undoRedoService->index++;
    return 1;
}

/*
int getIndex(UndoRedoService *service){
    if (service == NULL)
        return -1;
    return service->index;
}*/
