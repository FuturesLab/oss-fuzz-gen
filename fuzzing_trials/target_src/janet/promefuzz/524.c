// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_mutex_init at janet.c:1442:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_deinit at janet.c:1449:6 in janet.h
// janet_os_mutex_init at janet.c:1442:6 in janet.h
// janet_os_mutex_deinit at janet.c:1449:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "janet.h"

// Define the JanetOSMutex structure for the purpose of this fuzz driver
struct JanetOSMutex {
    pthread_mutex_t mutex;
};

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

int LLVMFuzzerTestOneInput_524(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0; // Not enough data to perform meaningful operations
    }

    // Initialize the mutex
    JanetOSMutex mutex;
    janet_os_mutex_init(&mutex);

    // Use the first byte of the input to determine the sequence of operations
    uint8_t operation = Data[0];

    // Perform operations based on the input
    switch (operation % 4) {
        case 0:
            // Lock and unlock the mutex
            janet_os_mutex_lock(&mutex);
            janet_os_mutex_unlock(&mutex);
            break;
        case 1:
            // Lock the mutex multiple times
            janet_os_mutex_lock(&mutex);
            janet_os_mutex_lock(&mutex);
            janet_os_mutex_unlock(&mutex);
            janet_os_mutex_unlock(&mutex);
            break;
        case 2:
            // Attempt to unlock without locking first
            // Avoid panic by ensuring the mutex is locked first
            janet_os_mutex_lock(&mutex);
            janet_os_mutex_unlock(&mutex);
            break;
        case 3:
            // Deinitialize without locking
            janet_os_mutex_deinit(&mutex);
            // Re-initialize to ensure proper cleanup
            janet_os_mutex_init(&mutex);
            break;
    }

    // Clean up resources
    janet_os_mutex_deinit(&mutex);

    return 0;
}