#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

typedef struct JanetOSRWLock {
    pthread_rwlock_t lock;
} JanetOSRWLock;

int LLVMFuzzerTestOneInput_1430(const uint8_t *Data, size_t Size) {
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