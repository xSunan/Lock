#include<stdio.h>
#include<stdlib.h>
#include "liblist.c"
#include "hash.h"


void Hash_Init(hash_t *hash, int buckets){
	hash->buckets = buckets;
	hash->bucket_lists = malloc(sizeof(list_t*)*buckets); 
}

void Hash_Insert(hash_t *hash, void *element, unsigned int key) {
	int idx = key%(hash->buckets);
	printf("indx: %d\n",idx);
	if (hash->bucket_lists[idx] == NULL){
		list_t *list = malloc(sizeof(list_t));
		List_Init(list);
		hash->bucket_lists[idx] = list; 
	}
	List_Insert(hash->bucket_lists[idx],element,key);
}

void Hash_Delete(hash_t *hash, unsigned int key) {
	int idx = key%(hash->buckets);
	list_t *list = hash->bucket_lists[idx];
	List_Delete(list,key);

}

void *Hash_Lookup(hash_t *hash, unsigned int key) {
	int idx = key%(hash->buckets);
	list_t *list = hash->bucket_lists[idx];
	void *res = List_Lookup(list,key);
	return res;
}

void print_hash(hash_t *hash){
	for(int i=0;i<hash->buckets;i++){
		
		if (hash->bucket_lists[i] != NULL){
			printf("%d :", i);
			print_list(hash->bucket_lists[i]);
		}
		
	}
}

int main(){
	hash_t *hash = malloc(sizeof(hash_t));
	Hash_Init(hash,5);
	void *element = malloc(sizeof(char));
	Hash_Insert(hash, element, 1);
	Hash_Insert(hash, element, 2);
	Hash_Insert(hash, element, 3);
	Hash_Insert(hash, element, 8);
	print_hash(hash);
	Hash_Delete(hash,2);
	print_hash(hash);

}