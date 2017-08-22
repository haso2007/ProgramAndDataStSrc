#include "queue.h"
2 #include <malloc.h>
3
4 #define MAXQSIZE 100
5 struct queueCDT{
6 queueElementT *data;
7 int front;
8 int rear;
9 };
10
11 queueADT newQueue(void)
12 {
13 queueADT queue;
14 queue = (queueADT)malloc(sizeof(struct queueCDT));
15 queue -> data = (queueElementT*)malloc(MAXQSIZE * sizeof(queueElementT));
16 queue -> front = 0;
17 queue -> rear = 0;
18 return queue;
19 }
20
21 void freeQueue(queueADT queue)
22 {
23 free(queue -> data);
24 free(queue);
25 }
26
27 bool inQueue(queueADT queue, queueElementT value)
28 {
29 if(queueIsFull(queue)) {
30 return false;
31 }
32 queue -> data[queue -> rear] = value;
33 queue -> rear = (queue->rear + 1) % MAXQSIZE;
34 return true;
35 }
36
37 bool outQueue(queueADT queue, queueElementT *p_value)
38 {
39 if(queueIsEmpty(queue)) {
40 return false;
41 }
42 *p_value = queue -> data[queue -> front];
43 queue -> front = (queue -> front + 1) % MAXQSIZE;
44 return true;
45 }
46
47 bool queueIsEmpty(queueADT queue)
48 {
49 return (queue -> rear == queue -> front);
50 }
51
52 bool queueIsFull(queueADT queue)
53 {
54 return ((queue->rear + 1) % MAXQSIZE == queue -> front);
55 }
56
57 size_t getQueueLength(queueADT queue)
58 {
59 return (queue -> rear ¨C queue -> front + MAXQSIZE) % MAXQSIZE;
60 }
