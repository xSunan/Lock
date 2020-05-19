#include <pthread.h> 
#include "spin.c"
typedef struct node_ {
	struct node_ *next;
	unsigned int key;
	void *element;
} Node;

typedef struct list_{
	Node *head;
	spinlock_t head_lock;
	// pthread_mutex_t head_lock;
} list_t;

void List_Init(list_t *list);
void List_Insert(list_t *list, void *element, unsigned int key);
void List_Delete(list_t *list, unsigned int key);
void *List_Lookup(list_t *list, unsigned int key);
void print_list(list_t *list);


// 1 2 3 4 5 6 7


// 1 2 3 4 5 6     -- - 4

// 1 2 3 5 6   

// ----------

// 1 2 3 4 5 6     ---- 5

// 4  


// 7 6 5 4 3 2 1