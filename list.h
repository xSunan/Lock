typedef struct node_ {
	struct node_ *next;
	unsigned int key;
	void *element;
} Node;

typedef struct list_{
	Node *head;
} list_t;

void List_Init(list_t *list);
void List_Insert(list_t *list, void *element, unsigned int key);
void List_Delete(list_t *list, unsigned int key);
void *List_Lookup(list_t *list, unsigned int key);
