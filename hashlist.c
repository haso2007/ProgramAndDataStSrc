#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hashlist.h"
/********* slist operation
************/
 int slist_add_head (slist_head_t *p_head, slist_node_t *p_node)
 {
	 p_node->p_next = p_head->p_next;
	 p_head->p_next = p_node;
	 return 0;
 }
slist_node_t *slist_next_get (slist_head_t *p_head, slist_node_t *p_pos)
 {
	 if (p_pos) { 
	 	return p_pos->p_next;
	 }
	 return NULL;
 }
slist_node_t *slist_begin_get (slist_head_t *p_head)
 {
 	return slist_next_get(p_head, p_head);
 }

 slist_node_t *slist_end_get (slist_head_t *p_head)
 {
 	return NULL;
 }
 
typedef int (*slist_node_process_t) (void *p_arg, slist_node_t *p_node);

int slist_foreach( slist_head_t *p_head, slist_node_process_t pfn_node_process, void *p_arg)
 {
	 slist_node_t *p_tmp, *p_end;
	 int ret;
	
	 if ((p_head == NULL) || (pfn_node_process == NULL)){
	 	return -1;
	 }
	 p_tmp = slist_begin_get(p_head);
	 p_end = slist_end_get(p_head);
	 
	 while (p_tmp != p_end){
		 ret = pfn_node_process(p_arg, p_tmp);
		 if (ret < 0) return ret; // fail and over
		 p_tmp = slist_next_get(p_head, p_tmp); 
	 }
	 return 0;
 }
 slist_node_t *slist_prev_get (slist_head_t *p_head, slist_node_t *p_pos)
 {
	 slist_node_t *p_tmp = p_head; 
	 while ((p_tmp != NULL) && (p_tmp->p_next != p_pos)) { 
	 	p_tmp = p_tmp->p_next;
	 }
	 return p_tmp;
 }
 
  slist_node_t *slist_tail_get (slist_head_t *p_head)
 {
 	return slist_prev_get(p_head, NULL);
 }

int slist_del (slist_head_t *p_head, slist_node_t *p_node)
 {
	 slist_node_t *p_prev = slist_prev_get(p_head, p_node);
	 if (p_prev) {
		 p_prev->p_next = p_node->p_next;
		 p_node->p_next = NULL;
		 return 0;
		}
	 return -1;
 }
int slist_init (slist_head_t *p_head)
 {
	 if (p_head == NULL){
	 	return -1;
	 }
	 p_head -> p_next = NULL;
	 return 0;
 }
 /****** hash operation group
 ********/
int hash_db_init (hash_db_t *p_hash, unsigned int size, unsigned int key_len,
 unsigned int value_len, hash_func_t pfn_hash)
 {
	 int i;
	 if ((p_hash == NULL) || (pfn_hash == NULL)){
	 	return -1;
	 }
	 p_hash->p_head = (slist_head_t *)malloc(size * sizeof(slist_head_t));
	 	if (p_hash -> p_head == NULL) {
	 	return -1;
	 }
	 for (i = 0; i < size; i++){
	 	slist_init(&p_hash -> p_head[i]);
	 }
		 p_hash -> size = size;
		 p_hash -> key_len = key_len;
		 p_hash -> value_len = value_len;
		 p_hash -> pfn_hash = pfn_hash;
		 return 0;
 } 
 int hash_db_add (hash_db_t *p_hash, const void *key, const void *value)
 {
 	int idx = p_hash -> pfn_hash(key); 
	char *p_mem = (char *)malloc(sizeof(slist_node_t) + p_hash -> key_len + p_hash -> value_len);
	if (p_mem == NULL) {
	return -1;
 	}
	 memcpy(p_mem + sizeof(slist_node_t), key, p_hash -> key_len);
	 memcpy(p_mem + sizeof(slist_node_t) + p_hash->key_len, value, p_hash->value_len); 
	 return slist_add_head(&p_hash -> p_head[idx], (slist_node_t *)p_mem); 
 }

 struct _node_find_ctx {
 void *key; 
 unsigned int key_len;
 slist_node_t *p_result; 
 };
 static int __hash_db_node_find (void *p_arg, slist_node_t *p_node)
 {
	 struct _node_find_ctx *p_info = (struct _node_find_ctx *)p_arg; //user para as the context of node
	 char *p_mem = (char *)p_node + sizeof(slist_node_t); //get the key store address
	
	 if (memcmp(p_mem, p_info->key, p_info->key_len) == 0) {//compare -> find the node
		 p_info->p_result = p_node;
		 return -1; 
	 }
	 return 0;
 }

 int hash_db_search(hash_db_t *p_hash, const void *key, void *value)
 {
	 int idx = p_hash->pfn_hash(key); //generate index from key id[]
	 struct _node_find_ctx info = {(void*)key, p_hash->key_len, NULL}; //initiate the des_node context
	 slist_foreach(&p_hash->p_head[idx], __hash_db_node_find, &info);//cb function __hash_db_node_find is hidden
	
	 if (info.p_result != NULL) {
		 memcpy(value, (char *)info.p_result, sizeof(slist_node_t)+p_hash->key_len+p_hash->value_len);
		 return 0;
	 }
	 return -1;
 }
 int hash_db_del (hash_db_t *p_hash, const void *key)
 {
	 int idx = p_hash->pfn_hash(key); 
	 struct _node_find_ctx info = {(void*)key, p_hash->key_len, NULL}; 
	 slist_foreach(&p_hash->p_head[idx], __hash_db_node_find, &info); 
	 if (info.p_result != NULL) {
		 slist_del(&p_hash->p_head[idx], info.p_result); 
		 free(info.p_result); 
		 return 0;
	 }
	 return -1;
 }
int hash_db_deinit (hash_db_t *p_hash)
 {
	 int i;
	 slist_node_t *p_node;
	 for (i = 0; i < p_hash->size; i++) { 
		 while (slist_begin_get(&p_hash->p_head[i]) != slist_end_get(&p_hash->p_head[i])) {
			 p_node = slist_begin_get(&p_hash->p_head[i]);
			 slist_del(&p_hash->p_head[i], p_node); 
			 free(p_node);
			 }
		 }
	 free(p_hash->p_head); 
	 return 0;
}


/*************** application level operation
************/
typedef struct _student{
char name[10]; 
char sex;
float height, weight; 
} student_t;

 int db_id_to_idx (unsigned char id[6]) 
 {
 int i;
 int sum = 0;
 for (i = 0; i < 6; i++){
 sum += id[0];
 }
 return sum % 250;
 }

 int student_info_generate (unsigned char *p_id, student_t *p_student) 
 {
	 int i;
	 for (i = 0; i < 6; i++) { 
	 	p_id[i] = rand();
	 }
	 for (i = 0; i < 9; i++) { 
	 	p_student->name[i] = (rand() % ('z' - 'a')) + 'a';
	 }
	 p_student->name[i]= '\0';
	 p_student->sex = (rand() & 0x01) ? 'F' : 'M'; 
	 p_student->height = (float)rand() / rand();
	 p_student->weight = (float)rand() / rand();
	 return 0;
 }
 int main ()
 {
 student_t stu;
 unsigned char id[6];
 int i;
 hash_db_t hash_students;

 hash_db_init(&hash_students, 250, 6, sizeof(student_t), (hash_func_t)db_id_to_idx);

 for (i = 0; i < 100; i++) {
	 student_info_generate(id, &stu); //radom 100 value_t
	 if (hash_db_search(&hash_students, id, &stu) == 0) { 
	 printf("ID already exist \n");
	 continue;
 	}
 printf("Add record ID : %02x%02x%02x%02x%02x%02x\n",id[0],id[1],id[2],id[3],id[4],id[5]);
 printf("it's message %s %c %.2f %.2f\n", stu.name, stu.sex, stu.height, stu.weight);
 if (hash_db_add(&hash_students, id, &stu) != 0) {
	 printf("Add Failed");
	 }
 }

 printf("Check ID: %02x%02x%02x%02x%02x%02x\n",id[0],id[1],id[2],id[3],id[4],id[5]);
 if (hash_db_search(&hash_students, id, &stu) == 0) {
 	printf("student info: %s %c %.2f %.2f\n", stu.name, stu.sex, stu.height, stu.weight);
 } 
 else {
 	printf("Not illegal ID \r\n");
 }
 hash_db_deinit(&hash_students);
 return 0;
}
