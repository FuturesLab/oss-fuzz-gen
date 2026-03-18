#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    // Declare and initialize a sqlite3_mutex object
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);

    // Ensure the mutex is not NULL
    if (mutex == NULL) {
        return 0;
    }

    // Lock the mutex to ensure it is held
    sqlite3_mutex_enter(mutex);

    // Call the function-under-test
    int result = sqlite3_mutex_held(mutex);

    // Unlock the mutex
    sqlite3_mutex_leave(mutex);

    // Free the mutex
    sqlite3_mutex_free(mutex);

    return 0;
}