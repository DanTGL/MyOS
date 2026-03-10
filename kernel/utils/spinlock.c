#include <arch/cpu.h>
#include <utils/spinlock.h>

int spin_lock(atomic_flag *lock)
{
    while (atomic_flag_test_and_set(lock)) {
        __arch_spin_wait();
    }

    return 0;
}

int spin_trylock(atomic_flag *lock)
{
    if (atomic_flag_test_and_set(lock)) {
        return -2; // TODO: return and set errno to EBUSY
    }

    return 0;
}

int spin_unlock(atomic_flag *lock)
{
    atomic_flag_clear(lock);

    return 0;
}
