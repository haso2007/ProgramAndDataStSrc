#include "validator.h"
bool validateRange(Validator *pThis, int value)
 {
 RangeValidator *pRangeValidator = (RangeValidator *)pThis;
 return pRangeValidator -> min <= value && value <= pRangeValidator -> max;
 }

 bool validateOddEven(Validator *pThis, int value)
 {
 OddEvenValidator *pOddEvenValidator = (OddEvenValidator *)pThis;
 return (!pOddEvenValidator -> isEven && (value % 2)) ||
 (pOddEvenValidator -> isEven && !(value % 2));
 }
 //in running time, change the argument value,method will rung the corresponding function
int main(int argc, char*argv[]){
RangeValidator rangeVal = newRangeValidator(0, 9);
OddEvenValidator oddval = newOddEvenValidator(1);
bool result = validatorCheck(&rangeVal,11);
printf("%d\n",result);
result = validatorCheck(&oddval,10);
printf("%d\n",result);
}
