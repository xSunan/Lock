#include <stdio.h>
#include "counter.h"

void Counter_Init(counter_t *c, int value) {
    c->count = value;
    // c->lock.flag = 0;
	if (pthread_mutex_init(&(c->lock), NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }
}
int Counter_GetValue(counter_t *c) {
    // spinlock_acquire(&c->lock);
    pthread_mutex_lock(&(c->lock));
    int res = c->count;
    // spinlock_release(&c->lock);
    pthread_mutex_unlock(&(c->lock));
    return res;
}
void Counter_Increment(counter_t *c) {
    // spinlock_acquire(&c->lock);
    pthread_mutex_lock(&(c->lock));
    c->count = c->count+1;
    // spinlock_release(&c->lock);
    pthread_mutex_unlock(&(c->lock));
}
void Counter_Decrement(counter_t *c) {
    // spinlock_acquire(&c->lock);
    pthread_mutex_lock(&(c->lock));
    c->count--;
    // spinlock_release(&c->lock);
    pthread_mutex_unlock(&(c->lock));
}

void thread_code(counter_t *c) {
    for (int i = 0; i < 100000; i++) {
        Counter_Increment(c);
    }
}

int main() {
    counter_t c;
    Counter_Init(&c, 0);


    pthread_t th1, th2;
    pthread_create(&th1, NULL, thread_code, &c);
    pthread_create(&th2, NULL, thread_code, &c);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    int val = Counter_GetValue(&c);
    printf("%d\n", val);

}