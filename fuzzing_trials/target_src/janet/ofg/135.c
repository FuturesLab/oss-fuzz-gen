#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <janet.h>

// Ensure the JanetOSRWLock structure is defined only if not already defined
#ifndef JANET_OS_RWLOCK_DEFINED
#define JANET_OS_RWLOCK_DEFINED
struct JanetOSRWLock {
    pthread_rwlock_t lock;
};
#endif

// Function to initialize the JanetOSRWLock
void janet_os_rwlock_init_135(JanetOSRWLock *rwlock) {
    pthread_rwlock_init(&rwlock->lock, NULL);
}

// Function to lock the JanetOSRWLock for reading
void janet_os_rwlock_rlock_135(JanetOSRWLock *rwlock) {
    pthread_rwlock_rdlock(&rwlock->lock);
}

// Function to unlock the JanetOSRWLock
void janet_os_rwlock_unlock(JanetOSRWLock *rwlock) {
    pthread_rwlock_unlock(&rwlock->lock);
}

// Fuzzing harness
int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    JanetOSRWLock rwlock;

    // Initialize the read-write lock
    janet_os_rwlock_init_135(&rwlock);

    // Call the function-under-test
    janet_os_rwlock_rlock_135(&rwlock);

    // Unlock the read-write lock
    janet_os_rwlock_unlock(&rwlock);

    return 0;
}