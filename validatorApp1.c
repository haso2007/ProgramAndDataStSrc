#include<stdio.h>
#include"StackADT.h"
#include"validator.h"

 bool pushWithValidate(stackADT stack, int value, Validator *pValidator)
 {
 if (pValidator && !pValidator -> validate(pValidator, value)){
 return false;
 }
 return push(stack, value);
 }

 int main(int argc, char *argv[])
 {
 stackADT stack;
 int temp;

 stack = newStack();

 RangeValidator rangeValidator = newRangeValidator(0, 9);
 for (int i = 0; i < 16; i++){
 pushWithValidate(stack, i, &rangeValidator.isa);
 }
 while(!stackIsEmpty(stack)){
 pop(stack, &temp);
 printf("%d ", temp);
 }
 printf("\n");
 OddEvenValidator oddEvenValidator = newOddEvenValidator(true);
 for (int i = 0; i < 16; i ++){
 pushWithValidate(stack, i, &oddEvenValidator.isa);
 }
 while (!stackIsEmpty(stack)) {
 pop(stack, &temp);
 printf("%d ", temp);
 }
 freeStack(stack);
 return 0;
 }
