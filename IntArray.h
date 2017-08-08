
 #include <stdbool.h>
 #include <stddef.h>

 typedef struct _IntArray IntArray;
 IntArray * IA_ini(); // ?? IntArray
 void IA_cleanup(IntArray *pThis); // ?? IntArray
 void IA_setSize(IntArray *pThis, size_t size); // ????????
 size_t IA_getSize(IntArray *pThis); // ????????
 bool IA_setElem(IntArray *pThis, size_t index, int value); // ??????
 bool IA_getElem(IntArray *pThis, size_t index, int *pValue); // ??????
