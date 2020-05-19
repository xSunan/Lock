#ifndef _COUNTERH_
#define _COUNTERH_

#include "spin.h"
#include <pthread.h>

typedef struct Counter{
    int count;
    spinlock_t lock;
    pthread_mutex_t pthread_lock;
} counter_t;

void Counter_Init(counter_t *c, int value);
int Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);

#endif
