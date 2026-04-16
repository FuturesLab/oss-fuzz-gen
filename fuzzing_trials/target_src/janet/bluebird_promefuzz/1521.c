#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include "janet.h"

typedef struct JanetOSRWLock {
    pthread_rwlock_t rwlock;
} JanetOSRWLock;

static void fuzz_janet_os_rwlock_rlock(const uint8_t *Data, size_t Size) {
    (void)Data; // Unused parameter
    (void)Size; // Unused parameter

    JanetOSRWLock rwlock;
    pthread_rwlock_init(&rwlock.rwlock, NULL);

    janet_os_rwlock_rlock(&rwlock);

    pthread_rwlock_destroy(&rwlock.rwlock);
}

static void fuzz_janet_os_rwlock_size(const uint8_t *Data, size_t Size) {
    (void)Data; // Unused parameter
    (void)Size; // Unused parameter

    size_t rwlock_size = janet_os_rwlock_size();
    (void)rwlock_size; // Use rwlock_size to avoid unused variable warning
}

static void fuzz_janet_os_mutex_size(const uint8_t *Data, size_t Size) {
    (void)Data; // Unused parameter
    (void)Size; // Unused parameter

    size_t mutex_size = janet_os_mutex_size();
    (void)mutex_size; // Use mutex_size to avoid unused variable warning
}

int LLVMFuzzerTestOneInput_1521(const uint8_t *Data, size_t Size) {
    fuzz_janet_os_rwlock_rlock(Data, Size);
    fuzz_janet_os_rwlock_size(Data, Size);
    fuzz_janet_os_mutex_size(Data, Size);

    return 0;
}