// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_rwlock_init at janet.c:1462:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_deinit at janet.c:1466:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

typedef struct JanetOSRWLock {
    pthread_rwlock_t lock;
} JanetOSRWLock;

int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetOSRWLock)) {
        return 0;
    }

    JanetOSRWLock *rwlock = malloc(sizeof(JanetOSRWLock));
    if (!rwlock) {
        return 0;
    }
    memset(rwlock, 0, sizeof(JanetOSRWLock)); // Ensure the structure is zero-initialized

    janet_os_rwlock_init(rwlock);

    if (Size % 2 == 0) {
        janet_os_rwlock_wlock(rwlock);
        janet_os_rwlock_wunlock(rwlock);
    } else {
        janet_os_rwlock_rlock(rwlock);
        janet_os_rwlock_runlock(rwlock);
    }

    janet_os_rwlock_deinit(rwlock);

    free(rwlock);
    return 0;
}