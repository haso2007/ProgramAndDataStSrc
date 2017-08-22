#include "StackADT.h"
#include <malloc.h>
 #define MAXSIZE 100
 struct stackCDT{
 int *data;
 size_t top;
 size_t numData;
 };

stackADT newStack()
 {
 stackADT stack;
 stack = (stackADT)malloc(sizeof(struct stackCDT));
 stack -> data = (int*)malloc(MAXSIZE*sizeof(int));
 stack -> top = 0;
 stack -> numData = MAXSIZE;
 return stack;
 }

 void freeStack(stackADT stack)
 {
 free(stack -> data);
 free(stack);
 }

 bool push(stackADT stack, stackElementT value)
 {
 if(stackIsFull(stack)) return false;
 stack -> data[stack -> top ++] = value;
 return true;
 }

 bool pop(stackADT stack, stackElementT *pValue)
 {
 if (stackIsEmpty(stack)) return false;
 *pValue = stack -> data[-- stack -> top];
 return true;
 }

 bool stackIsEmpty(stackADT stack)
 {
 return (stack -> top == 0);
 }

 bool stackIsFull(stackADT stack)
 {
 return (stack -> top == stack -> numData);
 }

 size_t getStackDepth(stackADT stack)
 {
 return (stack -> top);
 }

 bool getStackElement(stackADT stack, size_t index, stackElementT *pValue)
 {
 if (index > stack -> top) return false;
 *pValue = stack -> data[stack -> top - index - 1];
 return true;
 }
