#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int flag;  // 1-occupied, 0-unoccupied
} spinlock_t;

int xchg(volatile int *addr, int newval) {
    int result;
    asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
    return result;
}

void spinlock_acquire(spinlock_t *lock) {
    while (xchg(&lock->flag, 1)) {};
}

void spinlock_release(spinlock_t *lock) {
    lock->flag = 0;
}

int main() {

    spinlock_t lock={.flag=0};
    spinlock_acquire(&lock);
    spinlock_release(&lock);
    spinlock_acquire(&lock);

    printf("flag: %d\n", lock.flag);
}
