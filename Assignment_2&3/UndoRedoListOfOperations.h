#pragma once
#include "Medicine.h"
#include "Repository.h"
#include "DynamicArray.h"
//#include "Service.h"

//--------------------UndoRedoFunctions------------------------
typedef void (*undoRedoFct)(Repository*, char*, TInt, TInt, TInt);

//--------------------Operation------------------------
typedef struct
{
    undoRedoFct undoFunction;
    undoRedoFct redoFunction;
    Medicine* medicineToUndo;
    Medicine* medicineToRedo;
} Operation;

Operation *createOperation(undoRedoFct undo, undoRedoFct redo, Medicine *medicineToUndo, Medicine *medicineToRedo);
void destroyOperation(Operation* operation);

//--------------------UndoRedoService------------------------

typedef struct Service Service;

typedef struct {
    DynamicArray *operationStack;
    int index;
} UndoRedoService;

UndoRedoService *create_undoRedoService();

void destroy_undoRedoService(UndoRedoService *service);

void push_undoRedoService(UndoRedoService *s, Operation *operation);

int isEmpty(UndoRedoService *s);

int undo(Service *service);

int redo(Service *service);

int getIndex(UndoRedoService *service);


