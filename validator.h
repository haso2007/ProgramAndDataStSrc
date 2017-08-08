
//#pragma once;
#include <stdbool.h>
 typedef struct _Validator{
 bool (*const validate)(struct _Validator *pThis, int value);
 }Validator;
 typedef struct{
 Validator isa;
 const int min;
 const int max;
 } RangeValidator;

 typedef struct{
 Validator isa;
 bool isEven;
 }OddEvenValidator;

 extern bool validateRange(Validator *pThis, int value); 
 extern bool validateOddEven(Validator *pThis, int value); 
 #define newRangeValidator(min, max) {{validateRange}, (min), (max)}
 #define newOddEvenValidator(isEven) {{validateOddEven}, (isEven)}

 bool validatorCheck(void *pValidator, int value)
 {
 Validator *pthis = (Validator *)pValidator;
 return pthis->validate(pthis, value);
 }


