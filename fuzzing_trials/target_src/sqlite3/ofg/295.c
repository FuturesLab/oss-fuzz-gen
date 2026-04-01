#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Initialize a mutex
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);

    // Ensure the mutex is not NULL
    if (mutex == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = sqlite3_mutex_notheld(mutex);

    // Free the mutex
    sqlite3_mutex_free(mutex);

    return 0;
}