#pragma once;
#include <stdbool.h>
 #include <stddef.h>

 typedef int stackElementT;
 typedef struct stackCDT * stackADT;

 stackADT newStack();
 void freeStack(stackADT stack);
 bool push(stackADT stack, stackElementT value);
 bool pop(stackADT stack, stackElementT *pValue);
 bool stackIsEmpty(stackADT stack);
 bool stackIsFull(stackADT stack);
 size_t getStackDepth(stackADT stack);
 bool getStackElement(stackADT stack, size_t index, stackElementT *pValue);
