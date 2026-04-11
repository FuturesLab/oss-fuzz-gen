// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_os_mutex_init at janet.c:1442:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_lock at janet.c:1453:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_unlock at janet.c:1457:6 in janet.h
// janet_os_mutex_deinit at janet.c:1449:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <janet.h>

// Define the JanetOSMutex structure as required
struct JanetOSMutex {
    pthread_mutex_t mutex;
};

static void fuzz_janet_os_mutex_operations(JanetOSMutex *mutex) {
    // Initialize the mutex
    janet_os_mutex_init(mutex);

    // Lock and unlock the mutex in various patterns
    janet_os_mutex_lock(mutex);
    janet_os_mutex_unlock(mutex);

    // Attempt recursive locking
    janet_os_mutex_lock(mutex);
    janet_os_mutex_lock(mutex);
    janet_os_mutex_unlock(mutex);
    janet_os_mutex_unlock(mutex);

    // Deinitialize the mutex
    janet_os_mutex_deinit(mutex);
}

int LLVMFuzzerTestOneInput_624(const uint8_t *Data, size_t Size) {
    // Allocate space for a mutex
    JanetOSMutex *mutex = (JanetOSMutex *)malloc(sizeof(JanetOSMutex));
    if (!mutex) {
        return 0;
    }

    // Fuzz the mutex operations
    fuzz_janet_os_mutex_operations(mutex);

    // Free the allocated space
    free(mutex);

    return 0;
}