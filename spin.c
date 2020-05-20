#include "spin.h"

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
