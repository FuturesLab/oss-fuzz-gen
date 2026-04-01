#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_362(const uint8_t *data, size_t size) {
    sqlite3_mutex *mutex;

    // Initialize SQLite3 library
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Create a new mutex
    mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
    if (mutex == NULL) {
        sqlite3_shutdown();
        return 0;
    }

    // Enter the mutex
    sqlite3_mutex_enter(mutex);

    // Call the function-under-test
    int result = sqlite3_mutex_held(mutex);

    // Leave the mutex
    sqlite3_mutex_leave(mutex);

    // Free the mutex
    sqlite3_mutex_free(mutex);

    // Shutdown SQLite3 library
    sqlite3_shutdown();

    return 0;
}

#ifdef __cplusplus
}
#endif