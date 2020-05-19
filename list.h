#ifndef _LISTH_
#define _LISTH_

#include <pthread.h> 
#include "spin.h"

typedef struct node_ {
	struct node_ *next;
	unsigned int key;
	void *element;
} Node;

typedef struct list_{
	Node *head;
	spinlock_t head_lock;
	pthread_mutex_t head_pthread_lock;
} list_t;

void List_Init(list_t *list);
void List_Insert(list_t *list, void *element, unsigned int key);
void List_Delete(list_t *list, unsigned int key);
void *List_Lookup(list_t *list, unsigned int key);

#endif


