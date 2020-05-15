#include<stdio.h>
#include<stdlib.h>
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
		list->head = new_node;
	} else {
		new_node->next = list->head;
		list->head = new_node;
	}
	return;
}

void List_Delete(list_t *list, unsigned int key){
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
		}
		pre = cur;
		cur = cur->next;
	}
}

void *List_Lookup(list_t *list, unsigned int key){
	Node *cur = list->head;
	while (cur != NULL){
		if(cur->key == key){
			return cur;
		}
		cur = cur->next;
	}

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



// int main(){
// 	list_t *list = malloc(sizeof(list_t));
// 	List_Init(list);
// 	void *element = malloc(sizeof(char));
// 	List_Insert(list, element, 1);
// 	List_Insert(list, element, 2);
// 	List_Insert(list, element, 3);
// 	print(list);
// 	List_Delete(list,2);
// 	print(list);

// }

