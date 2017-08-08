
/*******slist class
******/
 typedef struct _slist_node{
 struct _slist_node *p_next;
 }slist_node_t;
typedef struct _slist_int{
 slist_node_t node; //include the slist node
// int data;
 }slist_int_t;

typedef slist_node_t slist_head_t;
typedef unsigned int (*hash_func_t) (const void *key); 

typedef struct _hash_db{
 slist_head_t *p_head; 
 unsigned int size;
 unsigned int value_len; 
 unsigned int key_len; 
 hash_func_t pfn_hash; 
 }hash_db_t;

 int hash_db_init (hash_db_t *p_hash, 
 unsigned int size,
 unsigned int key_len,
 unsigned int value_len,
 hash_func_t pfn_hash);

 int hash_db_add (hash_db_t *p_hash, const void *key,const void *value);
 int hash_db_del (hash_db_t *p_hash, const void *key); 
 int hash_db_search(hash_db_t *p_hash, const void *key, void *value); 
 int hash_db_deinit (hash_db_t *p_hash);
