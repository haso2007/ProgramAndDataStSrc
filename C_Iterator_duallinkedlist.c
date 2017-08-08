#include <stdio.h>
#include "C_iterator_duallinklist.h"

/** @defgroup DualLinedList operation
  */ 
 int dlist_init(dlist_head_t *p_head)
 {
	 if (p_head == NULL){
	 return -1;
	 }
	 p_head -> p_next = p_head;
	 p_head -> p_prev = p_head;
	 return 0;
 }
 dlist_node_t *dlist_prev_get(dlist_head_t *p_head, dlist_node_t *p_pos)
 {
 if (p_pos != NULL){
 return p_pos -> p_prev;
 }
 return NULL;
 }

 dlist_node_t *dlist_next_get(dlist_head_t *p_head, dlist_node_t *p_pos)
 {
	 if (p_pos != NULL){
	 return p_pos -> p_next;
	 }
	 return NULL;
 }
 dlist_node_t *dlist_tail_get(dlist_head_t *p_head)
 {
	 if (p_head != NULL) {
	 return p_head->p_prev;
 }
 return NULL;
 }
 dlist_node_t *dlist_begin_get(dlist_head_t *p_head)
 {
	 if (p_head != NULL){
	 return p_head->p_next;
	 }
	 return NULL;
 }
 dlist_node_t *dlist_end_get(dlist_head_t *p_head)
 {
	 if (p_head != NULL) {
	 return p_head->p_prev;
	 }
	 return NULL;
 }
//pfn_node_process will be implement in list_node_process
 int dlist_foreach (dlist_head_t *p_head,
 dlist_node_process_t pfn_node_process,
 void *p_arg)
 {
	 dlist_node_t *p_tmp, *p_end;
	 int ret;
	
	 if ((p_head == NULL) || (pfn_node_process == NULL)) {
	 return -1;
	 }
	
	 p_tmp = dlist_begin_get(p_head);
	 p_end = dlist_end_get(p_head);
	
	 while (p_tmp != p_end) {
	 ret = pfn_node_process(p_arg, p_tmp);
	 if (ret < 0) { 
	 return ret;
	 }
	 p_tmp = dlist_next_get(p_head, p_tmp); // ??§Ý§Ñ???
	 }
	 return 0;
 }
 int dlist_add (dlist_head_t *p_head, dlist_node_t *p_pos, dlist_node_t *p_node)
 {
 if ((p_head == NULL) || (p_pos == NULL) || (p_node == NULL)){
 return -1;
 }
 p_node->p_prev = p_pos;
 p_node->p_next = p_pos->p_next; 
 p_pos->p_next->p_prev = p_node; 
 p_pos->p_next = p_node;
 return 0;
 }

 int dlist_add_tail (dlist_head_t *p_head, dlist_node_t *p_node)
 {
 return dlist_add(p_head, p_head->p_prev, p_node);
}

/**
  * @}
  */ 
    
/** @defgroup Iterator operation
  */ 
void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next, iterator_prev_t pfn_prev)
 {
	 p_if -> pfn_next = pfn_next;//interface function means the function will assign,the interface object will use which operation
	 p_if -> pfn_prev = pfn_prev;
 }
 void iterator_next(iterator_if_t *p_if, iterator_t *p_iter)//make this function as virtual function 
 {	
 p_if -> pfn_next(p_iter);//this operation will realized by object p_if's operation 
 }

 void iterator_prev(iterator_if_t *p_if, iterator_t *p_iter)
 {
 p_if -> pfn_prev(p_iter);
 }

 static void __dlist_iterator_next(iterator_t *p_iter) 
 {
 *p_iter = ((dlist_node_t *)*p_iter) -> p_next;
 }

 static void __dlist_iterator_prev(iterator_t *p_iter) 
 {
 	*p_iter = ((dlist_node_t *)*p_iter) -> p_prev;
 }
 void dlist_iterator_if_get(iterator_if_t *p_if)
 {
 	iterator_if_init(p_if, __dlist_iterator_next, __dlist_iterator_prev);
 }

 int list_node_process(void *p_arg, dlist_node_t *p_node)
 {
	 printf("%d ", ((dlist_int_t *)p_node) -> data);
	 return 0;
 }

 static int __compare(iterator_t it1, iterator_t it2)
 {
 return ((dlist_int_t *)it1) -> data - ((dlist_int_t *)it2) -> data;
 }

 static void __swap(iterator_t it1, iterator_t it2)
 {
 int data = ((dlist_int_t *)it2) -> data;
 ((dlist_int_t *)it2) -> data = ((dlist_int_t *)it1) -> data;
 ((dlist_int_t *)it1) -> data = data;
 } 
//arithmetic is stable, but the variable part packing in interface compare_t and swat_p
void iter_sort(iterator_if_t *p_if, iterator_t begin, iterator_t end, compare_t compare, swap_t swap)
 {
	 int flag = 1; // flag = 1???????????
	 iterator_t it1 = begin; // it1 ???????‚T??
	 iterator_t it2 = end;
	
	 iterator_t it_next; // pNext ?? p1 ???????§Ý§Ñ???
	 if (begin == end) { // ????????????
		 return;
		 }
	 iterator_prev(p_if, &it2); 
	 while (it2 != begin){
	 it1 = begin;
	 flag = 1;
	 while(it1 != it2){
	 it_next = it1; // ??
	 iterator_next(p_if, &it_next); 
	 if(compare(it1, it_next) > 0){
		 swap(it1, it_next); // ????
		 flag = 0; 
		 }
	 it1 = it_next; 
	 	}
	 if(flag) return; 
		 iterator_prev(p_if, &it2); 
		}
 }

/**
 * @}
 */ 
 
//Client using the random number to do the test
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 int main(int argc, char *argv[])
 {
 const int MaxNodeCnt = 100;
 iterator_if_t iterator_if;
 dlist_head_t head; 
 dlist_int_t node[MaxNodeCnt]; 
 int i;

 dlist_init(&head);
 srand(time(NULL));
 for (i = 0; i < MaxNodeCnt; i++) { 
 node[i].data = rand(); 
 dlist_add_tail(&head, &(node[i].node));
 }
 //all above only dlist class
 dlist_iterator_if_get(&iterator_if);//define the interator use the dlist object,use the dlist obect operation

 printf("\nBefore bubble sort:\n");
 dlist_foreach (&head, list_node_process, NULL);//use list_node_process,

 iter_sort(&iterator_if, dlist_begin_get(&head), dlist_end_get(&head),__compare, __swap);

 printf("\nAfter bubble sort:\n");
 dlist_foreach (&head, list_node_process, NULL); 
 return 0;
}
