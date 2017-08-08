#ifndef __ITERATOR_H__
#define __ITERATOR_H__

 #include <stdio.h>
 #include <stdbool.h>
/* duallinkedlist Class*/
 typedef struct _dlist_node{
 struct _dlist_node *p_next; 
 struct _dlist_node *p_prev; 
 }dlist_node_t;
 
typedef struct _dlist_int{
 dlist_node_t node; 
 int data; //data type is int, in fact should be any data-type
 }dlist_int_t;

 typedef dlist_node_t dlist_head_t;

 typedef int (*dlist_node_process_t) (void *p_arg, dlist_node_t *p_node);

 int dlist_init (dlist_head_t *p_head); 

 int dlist_add (dlist_head_t *p_head, dlist_node_t *p_pos, dlist_node_t *p_node); 
 int dlist_add_tail(dlist_head_t *p_head, dlist_node_t *p_node); 
 int dlist_add_head (dlist_head_t *p_head, dlist_node_t *p_node);
 int dlist_del (dlist_head_t *p_head, dlist_node_t *p_node); 

 dlist_node_t *dlist_prev_get (dlist_head_t *p_head, dlist_node_t *p_pos); 
 dlist_node_t *dlist_next_get (dlist_head_t *p_head, dlist_node_t *p_pos); 
 dlist_node_t *dlist_tail_get (dlist_head_t *p_head);  
 dlist_node_t *dlist_begin_get (dlist_head_t *p_head);  
 dlist_node_t *dlist_end_get (dlist_head_t *p_head); 

 int dlist_foreach (dlist_head_t *p_head,
 dlist_node_process_t pfn_node_process,
 void *p_arg);


/* Iterator Class*/
//virtaul operation,need realization in concrete class
typedef void *iterator_t; 
typedef void (*iterator_next_t)(iterator_t *p_iter);
typedef void (*iterator_prev_t)(iterator_t *p_iter);
typedef int (*compare_t)(iterator_t it1, iterator_t it2);
typedef void (*swap_t)(iterator_t it1, iterator_t it2);
//迭代器接口，if:interface, 迭代器，这个接口包含两个虚方法 
 typedef struct _iterator_if{
 iterator_next_t pfn_next; //调用迭代器后移的函数指针，相当于P1++ 
 iterator_prev_t pfn_prev; 
 }iterator_if_t;
 
 void iterator_if_init(iterator_if_t *p_if, iterator_next_t pfn_next, iterator_prev_t pfn_prev);
 void iterator_next(iterator_if_t *p_if, iterator_t *p_iter); // ++
 void iterator_prev(iterator_if_t *p_if, iterator_t *p_iter); //--
 #endif
