#include <malloc.h>
#include "IntArray.h"

 struct _IntArray{
 int *pBuffer;
 size_t count;
 };

 IntArray * IA_ini()
 {
 IntArray *pIntArray = malloc(sizeof(IntArray));

 pIntArray -> pBuffer = 0;
 pIntArray -> count = 0;
 return pIntArray;
 }

 void IA_cleanup(IntArray *pThis)
 {
 free(pThis -> pBuffer);
 pThis -> pBuffer = 0;
 free(pThis);
 }

 void IA_setSize(IntArray *pThis, size_t size)
 {
 pThis -> count = size;
 pThis -> pBuffer = (int *)realloc(pThis -> pBuffer, size * sizeof(int));
 }

 size_t IA_getSize(IntArray *pThis)
 {
 return pThis -> count;
 }

 bool IA_setElem(IntArray *pThis, size_t index, int value)
 {
 if (index >= pThis -> count) return false;
 pThis -> pBuffer[index] = value;
 return true;
 }

 bool IA_getElem(IntArray *pThis, size_t index, int *pValue)
 {
 if (index >= pThis -> count) return false;
 *pValue = pThis -> pBuffer[index];
 return true;
 }
 
 int main()
 {
 IntArray *pIntArray;
 const size_t count = 10;
 int temp = 0;

 pIntArray=IA_ini();
 IA_setSize(pIntArray, count);
 for (size_t i = 0; i < count; i++)
 IA_setElem(pIntArray, i, (int)i * 2);
 for (size_t i = 0; i < count; i++){
 IA_getElem(pIntArray, i, &temp);
 printf("%d ", temp);
 }
 IA_cleanup(pIntArray);
 return 0;
 }
