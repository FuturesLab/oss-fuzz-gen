#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a mutex
    if (size < 1) { // Check if size is greater than zero
        return 0;
    }

    // Create a mutex object
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
    if (mutex == NULL) {
        return 0; // Ensure mutex is not NULL
    }

    // Call the function under test
    sqlite3_mutex_enter(mutex);

    // Clean up
    sqlite3_mutex_leave(mutex);
    sqlite3_mutex_free(mutex);

    return 0;
}