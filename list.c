#include "list.h"

/* create and initiate node */
Node* create_node(void *element, unsigned int key){
	Node *new_node = malloc(sizeof(Node));
	new_node->element = element;
	new_node->key = key;
	new_node->next = NULL;
	
	return new_node;
}

/* destroy the node and free the memory */
void destroy_node(Node *node){
	node->element=NULL;
	node->next=NULL;
	free(node);
}

void lock_acquire(list_t *list){
	#ifdef pthreadlock
	pthread_mutex_lock(&(list->head_pthread_lock));
	#else
	spinlock_acquire(&list->head_lock);
	#endif
}

void lock_release(list_t *list){
	#ifdef pthreadlock
	pthread_mutex_unlock(&(list->head_pthread_lock));
	#else
	spinlock_release(&list->head_lock);
	#endif
}

void lock_init(list_t *list){
	#ifdef pthreadlock
	if (pthread_mutex_init(&(list->head_pthread_lock), NULL) != 0){
        printf("\n mutex init failed\n");
    }
    #else
    list->head_lock.flag=0;
    #endif
}
/* Init the list */
void List_Init(list_t *list) {
	list->head = NULL;

	// init lock
	lock_init(list);
}

void List_Insert(list_t *list, void *element, unsigned int key){
	if(list==NULL)
		return;

	Node *new_node = create_node(element, key);

	/* thread safe */
	lock_acquire(list);
	
	if (list->head == NULL){
		list->head = new_node;
	} else {
		new_node->next = list->head;
		list->head = new_node;
	}

	/* release the lock */
	lock_release(list);
	return;
}

void List_Delete(list_t *list, unsigned int key){
	if (list==NULL){
		return;
	}
	/* lock the list */
	lock_acquire(list);

	/* check the validity of the list */
	if(list->head == NULL){
		lock_release(list);
		return;
	}

	Node *cur = list->head;
	Node *pre = NULL;

	/* traverse the list to find the element*/
	while (cur != NULL){
		if (cur->key == key){
			if (pre == NULL){
				list->head = cur->next;
			} else {
				pre->next = cur->next;		
			}
			destroy_node(cur);
			
			break;
		}
		pre = cur;
		cur = cur->next;
	}

	/* release the lock */
	lock_release(list);
}


void *List_Lookup(list_t *list, unsigned int key){

	/* check the validity of the list */
	if(list==NULL)
		return NULL;
	
	/* lock the list*/
	lock_acquire(list);

	if (list->head==NULL){
		return NULL;
	}
	/* traverse the list */
	Node *cur = list->head;
	while (cur != NULL){

		/* find the key */
		if(cur->key == key){
			lock_release(list);
			return cur;
		}
		
		cur = cur->next;
	}

	/* haven't find the key*/
	lock_release(list);

	return NULL;

}

// int main(){
// 	list_t *list = malloc(sizeof(list_t));
// 	void *element = malloc(sizeof(char));
// 	List_Insert(list,element,1);
// 	List_Insert(list,element,2);
// }




