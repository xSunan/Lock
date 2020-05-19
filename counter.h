#include "spin.c"
#include <pthread.h>

typedef struct Counter{
    int count;
    // spinlock_t lock;
    pthread_mutex_t lock;
} counter_t;

void Counter_Init(counter_t *c, int value);
int Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);