#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include "list.h"

Node* create_node(void *element, unsigned int key){
	Node *new_node = malloc(sizeof(Node));
	new_node->element = element;
	new_node->key = key;
	new_node->next = NULL;
	
	return new_node;
}

void destroy_node(Node *node){
	node->element=NULL;
	node->next=NULL;

	// node->node_lock = NULL;
	free(node);
}

void List_Init(list_t *list) {
	list->head = NULL;
	if (pthread_mutex_init(&(list->head_lock), NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }
}

void List_Insert(list_t *list, void *element, unsigned int key){
	// printf("adding\n");
	Node *new_node = create_node(element, key);
	pthread_mutex_lock(&(list->head_lock));
	if (list->head == NULL){
		list->head = new_node;
	} else {
		new_node->next = list->head;
		list->head = new_node;
	}
	pthread_mutex_unlock(&(list->head_lock));

	return;
}

void List_Delete(list_t *list, unsigned int key){
	pthread_mutex_lock(&(list->head_lock));

	if(list==NULL || list->head == NULL){
		pthread_mutex_unlock(&(list->head_lock));

		// printf("null return\n");
		return;
	}
	Node *cur = list->head;
	Node *pre = NULL;
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
	pthread_mutex_unlock(&(list->head_lock));
}


void *List_Lookup(list_t *list, unsigned int key){
	if(list==NULL || list->head==NULL)
		return NULL;
	// printf("looking up\n");
	pthread_mutex_lock(&(list->head_lock));
	Node *cur = list->head;
	while (cur != NULL){
		if(cur->key == key){
			pthread_mutex_unlock(&(list->head_lock));
			return cur;
		}
		
		cur = cur->next;
	}
	pthread_mutex_unlock(&(list->head_lock));

	return NULL;

}

void print_list(list_t *list){
	if (list==NULL)
		return;
	//printf("%d\n",list==NULL );

	Node *cur = list->head;
	int i=0;
	while (cur != NULL){
		printf("The element %d: %d\n", i,cur->key);
		i++;
		cur = cur->next;
	}
}

typedef struct args{
	list_t *list;
	unsigned int key;
	void *element;
	int thread;

} Args;


// void test_delete(void *args){
// 	Args *arg = (Args *) args;
// 	// printf("here thread: %d  head==null: %d\n", arg->thread, arg->list->head==NULL);
// 	// print_list(arg->list);
// 	List_Delete(arg->list, arg->key, arg->thread);
// 	printf("finish\n");
// }

// void test_insert(void *args){
// 	Args *arg = (Args *) args;
// 	// printf("thread: %d  head: %d\n", arg->thread, arg->list->head->key);
// 	// print_list(arg->list);
// 	List_Insert(arg->list, arg->element,arg->key, arg->thread);
// }

// void test_lookup(void *args){
// 	Args *arg = (Args *) args;
// 	// printf("thread: %d  head: %d\n", arg->thread, arg->list->head->key);
// 	// print_list(arg->list);
// 	List_Lookup(arg->list, arg->key);
// }

// int main(){
// 	// printf("here");
// 	int thread_num=10;
// 	pthread_t *threads = malloc(thread_num * sizeof(pthread_t));
// 	list_t *list = malloc(sizeof(list_t));
	

// 	List_Init(list);
// 	void *element = malloc(sizeof(char));
// 	List_Insert(list, element, 1,0);
// 	// List_Delete(list, 1,1);
// 	// List_Delete(list, 2,2);
// 	// List_Delete(list, 3,2);
// 	// List_Delete(list, 4,2);

// 	printf("%d\n",list==NULL );
// 	List_Insert(list, element, 2,0);
// 	List_Insert(list, element, 3,0);
// 	List_Insert(list, element, 4,0);
// 	List_Insert(list, element, 5,0);
// 	List_Insert(list, element, 6,0);
// 	List_Insert(list, element, 7,0);
// 	// print_list(list);
	
// 	Args *args = malloc(sizeof(Args)*thread_num);
// 	for(int i=0;i<thread_num/2;i++){
// 		args[i].list = list;
// 		args[i].key = i;
// 		args[i].thread = i;
// 		args[i].element = malloc(sizeof(char));
// 		// printf("here %d thread:%d\n", list->head->key, i);
// 		// List_Delete(list, i,i);
// 		pthread_create(threads+i, NULL, &test_delete, &args[i]);
// 		// pthread_create(threads+i, NULL, &test_insert, &args[i]);
// 		pthread_create(threads+i+thread_num/2, NULL, &test_lookup, &args[i]);
// 	}
// 	for( int t = 0; t < thread_num; t++ )
// 	{
// 		if(pthread_join(threads[t], NULL))
// 		{
// 			printf("Error joining thread\n");
// 			exit(2);
// 		}
// 	}
// 	printf("final\n");
// 	print_list(list);
// 	// List_Delete(list,2);

// }

