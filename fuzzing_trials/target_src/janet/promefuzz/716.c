// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_init at janet.c:1462:6 in janet.h
// janet_os_rwlock_deinit at janet.c:1466:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "janet.h"

struct JanetOSRWLock {
    // This struct should be defined according to the actual implementation details
    // For example, a pthread_rwlock_t or similar could be used
    void *internal_lock; // Placeholder for actual lock data
};

static void fuzz_rwlock_operations(JanetOSRWLock *rwlock, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    switch (Data[0] % 6) {
        case 0:
            janet_os_rwlock_rlock(rwlock);
            janet_os_rwlock_runlock(rwlock);
            break;
        case 1:
            janet_os_rwlock_wlock(rwlock);
            janet_os_rwlock_wunlock(rwlock);
            break;
        case 2:
            janet_os_rwlock_rlock(rwlock);
            janet_os_rwlock_rlock(rwlock);
            janet_os_rwlock_runlock(rwlock);
            janet_os_rwlock_runlock(rwlock);
            break;
        case 3:
            janet_os_rwlock_wlock(rwlock);
            janet_os_rwlock_wlock(rwlock);
            janet_os_rwlock_wunlock(rwlock);
            janet_os_rwlock_wunlock(rwlock);
            break;
        case 4:
            janet_os_rwlock_rlock(rwlock);
            janet_os_rwlock_wlock(rwlock);
            janet_os_rwlock_runlock(rwlock);
            janet_os_rwlock_wunlock(rwlock);
            break;
        case 5:
            janet_os_rwlock_wlock(rwlock);
            janet_os_rwlock_rlock(rwlock);
            janet_os_rwlock_wunlock(rwlock);
            janet_os_rwlock_runlock(rwlock);
            break;
    }
}

int LLVMFuzzerTestOneInput_716(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's data to process

    JanetOSRWLock rwlock;
    memset(&rwlock, 0, sizeof(JanetOSRWLock)); // Ensure the lock is zero-initialized
    janet_os_rwlock_init(&rwlock);
    
    fuzz_rwlock_operations(&rwlock, Data, Size);
    
    janet_os_rwlock_deinit(&rwlock);
    return 0;
}