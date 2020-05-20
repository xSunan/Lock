#ifndef _HASHH_
#define _HASHH_

#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct hashtable {
	list_t **bucket_lists;
	int buckets;
} hash_t;

void Hash_Init(hash_t *hash, int buckets);
void Hash_Insert(hash_t *hash, void *element, unsigned int key);
void Hash_Delete(hash_t *hash, unsigned int key);
void *Hash_Lookup(hash_t *hash, unsigned int key);
#endif
