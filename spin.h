#ifndef _SPINH_
#define _SPINH_
typedef struct {
    int flag;  // 1-occupied, 0-unoccupied
} spinlock_t;

int xchg(volatile int *addr, int newval);
void spinlock_acquire(spinlock_t *lock);
void spinlock_release(spinlock_t *lock);
#endif
