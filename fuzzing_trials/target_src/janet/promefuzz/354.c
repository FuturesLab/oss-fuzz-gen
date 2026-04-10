// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_rwlock_init at janet.c:1462:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_deinit at janet.c:1466:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

// Define a dummy struct since the actual size is unknown
struct JanetOSRWLock {
    char dummy[64]; // Assume a size that is likely sufficient
};

// Fuzz driver entry point
int LLVMFuzzerTestOneInput_354(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct JanetOSRWLock)) {
        return 0;
    }

    JanetOSRWLock rwlock;
    
    // Initialize the read-write lock
    janet_os_rwlock_init(&rwlock);

    // Randomly decide to acquire a read or write lock based on input data
    if (Data[0] % 2 == 0) {
        janet_os_rwlock_rlock(&rwlock);
        janet_os_rwlock_runlock(&rwlock);
    } else {
        janet_os_rwlock_wlock(&rwlock);
        janet_os_rwlock_wunlock(&rwlock);
    }

    // Deinitialize the read-write lock
    janet_os_rwlock_deinit(&rwlock);

    return 0;
}