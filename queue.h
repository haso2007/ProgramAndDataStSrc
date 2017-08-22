 #include <stdbool.h>
 #include <stddef.h>

 typedef int queueElementT;
 typedef struct queueCDT * queueADT;

 queueADT newQueue(void);
 void freeQueue(queueADT queue);
 bool inQueue(queueADT queue, queueElementT value);
 bool outQueue(queueADT queue, queueElementT *p_alue);
 bool queueIsEmpty(queueADT queue);
 bool queueIsFull(queueADT queue);
 size_t getQueueLength(queueADT queue);
