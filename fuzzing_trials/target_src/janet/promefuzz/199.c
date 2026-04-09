// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_rwlock_init at janet.c:1462:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_rlock at janet.c:1470:6 in janet.h
// janet_os_rwlock_runlock at janet.c:1478:6 in janet.h
// janet_os_rwlock_wlock at janet.c:1474:6 in janet.h
// janet_os_rwlock_wunlock at janet.c:1482:6 in janet.h
// janet_os_rwlock_deinit at janet.c:1466:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>
#include <pthread.h>

/* Define the JanetOSRWLock structure */
struct JanetOSRWLock {
    pthread_rwlock_t lock;
};

static void fuzz_rwlock_operations(JanetOSRWLock *rwlock, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    /* Initialize the lock */
    janet_os_rwlock_init(rwlock);

    for (size_t i = 0; i < Size; i++) {
        switch (Data[i] % 6) {
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
                break;
            case 3:
                janet_os_rwlock_runlock(rwlock);
                break;
            case 4:
                janet_os_rwlock_wlock(rwlock);
                break;
            case 5:
                janet_os_rwlock_wunlock(rwlock);
                break;
        }
    }

    /* Deinitialize the lock */
    janet_os_rwlock_deinit(rwlock);
}

int LLVMFuzzerTestOneInput_199(const uint8_t *Data, size_t Size) {
    JanetOSRWLock rwlock;
    fuzz_rwlock_operations(&rwlock, Data, Size);
    return 0;
}