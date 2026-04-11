// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "janet.h"

typedef struct JanetOSMutex {
    pthread_mutex_t mutex;
} JanetOSMutex;

static void initialize_mutex(JanetOSMutex *mutex) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex->mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

static void deinitialize_mutex(JanetOSMutex *mutex) {
    pthread_mutex_destroy(&mutex->mutex);
}

static void lock_mutex(JanetOSMutex *mutex) {
    pthread_mutex_lock(&mutex->mutex);
}

static void unlock_mutex(JanetOSMutex *mutex) {
    pthread_mutex_unlock(&mutex->mutex);
}

int LLVMFuzzerTestOneInput_295(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    JanetOSMutex mutex;
    janet_init();  // Initialize the Janet VM
    initialize_mutex(&mutex);

    // Explore different states based on input data
    for (size_t i = 0; i < Size; i++) {
        switch (Data[i] % 4) {
            case 0:
                lock_mutex(&mutex);
                break;
            case 1:
                unlock_mutex(&mutex);
                break;
            case 2:
                // Attempt to lock and unlock multiple times
                lock_mutex(&mutex);
                unlock_mutex(&mutex);
                break;
            case 3:
                // Attempt nested locking
                lock_mutex(&mutex);
                lock_mutex(&mutex);
                unlock_mutex(&mutex);
                unlock_mutex(&mutex);
                break;
        }
    }

    deinitialize_mutex(&mutex);
    janet_deinit();  // Deinitialize the Janet VM
    return 0;
}