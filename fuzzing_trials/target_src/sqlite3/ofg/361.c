#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_361(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a mutex
    if (size < sizeof(sqlite3_mutex *)) { // Use pointer size instead of incomplete type
        return 0;
    }

    // Create a mutex
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);

    // Check if the mutex is held
    if (mutex != NULL) { // Ensure the mutex is not NULL before using it
        int result = sqlite3_mutex_held(mutex);

        // Free the mutex
        sqlite3_mutex_free(mutex);
    }

    return 0;
}