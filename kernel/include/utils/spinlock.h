#ifndef _KERNEL_UTILS_SPINLOCK_H
#define _KERNEL_UTILS_SPINLOCK_H

#include <stdatomic.h>

int spin_lock(atomic_flag *lock);
int spin_trylock(atomic_flag *lock);
int spin_unlock(atomic_flag *lock);

#endif // !_KERNEL_UTILS_SPINLOCK_H
