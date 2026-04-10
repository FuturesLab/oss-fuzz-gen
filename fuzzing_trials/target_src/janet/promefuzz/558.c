// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_rwlock_init at janet.c:1462:6 in janet.h
// janet_os_rwlock_deinit at janet.c:1466:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>
#include <pthread.h>

// Define the JanetOSRWLock structure as it is expected to contain a pthread_rwlock_t
struct JanetOSRWLock {
    pthread_rwlock_t lock;
};

static void initialize_rwlock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_init(rwlock);
}

static void deinitialize_rwlock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_deinit(rwlock);
}

static void acquire_write_lock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_wlock(rwlock);
}

static void release_write_lock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_wunlock(rwlock);
}

static void acquire_read_lock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_rlock(rwlock);
}

static void release_read_lock(JanetOSRWLock *rwlock) {
    janet_os_rwlock_runlock(rwlock);
}

int LLVMFuzzerTestOneInput_558(const uint8_t *Data, size_t Size) {
    // Allocate memory for JanetOSRWLock
    JanetOSRWLock *rwlock = (JanetOSRWLock *)malloc(sizeof(JanetOSRWLock));
    if (!rwlock) {
        return 0; // Allocation failed
    }

    initialize_rwlock(rwlock);

    // Use the first byte to decide the operation
    if (Size > 0) {
        switch (Data[0] % 6) {
            case 0:
                acquire_write_lock(rwlock);
                release_write_lock(rwlock);
                break;
            case 1:
                acquire_read_lock(rwlock);
                release_read_lock(rwlock);
                break;
            case 2:
                acquire_write_lock(rwlock);
                break;
            case 3:
                acquire_read_lock(rwlock);
                break;
            case 4:
                release_write_lock(rwlock);
                break;
            case 5:
                release_read_lock(rwlock);
                break;
        }
    }

    deinitialize_rwlock(rwlock);
    free(rwlock);
    return 0;
}