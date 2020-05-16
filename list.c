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
	free(node);
}

void List_Init(list_t *list) {
	list->head = NULL;
}

void List_Insert(list_t *list, void *element, unsigned int key){
	Node *new_node = create_node(element, key);
	if (list->head == NULL){
		pthread_mutex_lock(&(list->head_lock));
		list->head = new_node;
		pthread_mutex_unlock(&(list->head_lock));
	} else {
		pthread_mutex_lock(&(list->head_lock));
		new_node->next = list->head;
		list->head = new_node;
		pthread_mutex_unlock(&(list->head_lock));
	}
	return;
}

void List_Delete(list_t *list, unsigned int key){
	if(list==NULL)
		return;
	if(list->head != NULL)
		pthread_mutex_lock(&(list->head->node_lock));
	
	Node *cur = list->head;

	Node *pre = NULL;
	while (cur != NULL){
		pthread_mutex_unlock(&(cur->node_lock));
		pthread_mutex_lock(&(cur->node_lock));
		printf("tranverse: %d\n", cur->key);
		if(pre!=NULL)
			pthread_mutex_lock(&(pre->node_lock));
		
		if (cur->key == key){
			if (pre == NULL){
				// pthread_mutex_lock(&(list->head_lock));
				list->head = cur->next;
				// pthread_mutex_unlock(&(list->head_lock));
			} else {
				// pthread_mutex_lock(&(cur->node_lock));
				// pthread_mutex_lock(&(pre->node_lock));
				pre->next = cur->next;
				// pthread_mutex_unlock(&(pre->node_lock));
				// pthread_mutex_unlock(&(cur->node_lock));
			}
			destroy_node(cur);
		}
		pthread_mutex_lock(&(cur->next->node_lock));
		pre = cur;
		cur = cur->next;
		pthread_mutex_unlock(&(cur->next->node_lock));

		pthread_mutex_unlock(&(cur->node_lock));
		if(pre!=NULL)
			pthread_mutex_unlock(&(pre->node_lock));

	}
	printf("successfully delete %d\n", key);
}

void *List_Lookup(list_t *list, unsigned int key){
	if(list==NULL)
		return NULL;

	Node *cur = list->head;
	while (cur != NULL){
		if(cur->key == key){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;

}

void print_list(list_t *list){
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
	pthread_t thread;

} Args;


void test_delete(void *args){
	Args *arg = (Args *) args;
	List_Delete(arg->list, arg->key);
}


int main(){
	int thread_num=2;

	list_t *list = malloc(sizeof(list_t));
	List_Init(list);
	void *element = malloc(sizeof(char));
	List_Insert(list, element, 1);
	List_Insert(list, element, 2);
	List_Insert(list, element, 3);
	List_Insert(list, element, 4);
	List_Insert(list, element, 5);
	List_Insert(list, element, 6);
	List_Insert(list, element, 7);

	Args *args = malloc(sizeof(Args)*thread_num);
	for(int i=0;i<thread_num;i++){
		args[i].list = list;
		args[i].key = i+1;
		args[i].thread = i;
		printf("here\n");
		pthread_create(&args[i].thread, NULL, &List_Delete, &args[i]);
	}
	print_list(list);
	// List_Delete(list,2);

}

