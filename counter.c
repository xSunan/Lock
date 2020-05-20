#include "counter.h"

void lock_acquire(counter_t *c){
    #ifdef pthreadlock
    pthread_mutex_lock(&(c->pthread_lock));
    #else
    spinlock_acquire(&c->lock);
    #endif
}

void lock_release(counter_t *c){
    #ifdef pthreadlock
    pthread_mutex_unlock(&(c->pthread_lock));
    #else
    spinlock_release(&c->lock);
    #endif
}

void lock_init(counter_t *c){
    #ifdef pthreadlock
    if (pthread_mutex_init(&(c->pthread_lock), NULL) != 0){
        printf("\n mutex init failed\n");
    }
    #else
    c->lock.flag=0;
    #endif
}

void Counter_Init(counter_t *c, int value) {
    c->count = value;
	lock_init(c);
}
int Counter_GetValue(counter_t *c) {

    lock_acquire(c);
    int res = c->count;
    lock_release(c);
    return res;
}
void Counter_Increment(counter_t *c) {
    lock_acquire(c);
    c->count = c->count+1;
    lock_release(c);
}
void Counter_Decrement(counter_t *c) {
    lock_acquire(c);
    c->count--;
    lock_release(c);
}

void thread_code(counter_t *c) {
    for (int i = 0; i < 100000; i++) {
        Counter_Increment(c);
    }
}

// int main() {
//     counter_t c;
//     Counter_Init(&c, 0);


//     pthread_t th1, th2;
//     pthread_create(&th1, NULL, thread_code, &c);
//     pthread_create(&th2, NULL, thread_code, &c);
//     pthread_join(th1, NULL);
//     pthread_join(th2, NULL);
//     int val = Counter_GetValue(&c);
//     printf("%d\n", val);

// }