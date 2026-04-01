#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Fuzzing harness for sqlite3_mutex_notheld
int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    // Initialize SQLite mutex subsystem
    sqlite3_initialize();

    // Create a mutex
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);

    // Ensure the mutex is not NULL
    if (mutex != NULL) {
        // Use the first byte of data to decide whether to lock the mutex
        if (size > 0 && data[0] % 2 == 0) {
            // Lock the mutex to simulate it being held
            sqlite3_mutex_enter(mutex);
        }

        // Call the function-under-test
        int result = sqlite3_mutex_notheld(mutex);

        // Use the result in some way to avoid compiler optimizations
        if (result) {
            // Do something if the mutex is not held
        } else {
            // Do something if the mutex is held
        }

        // Ensure the mutex is unlocked before freeing
        if (sqlite3_mutex_notheld(mutex) == 0) {
            sqlite3_mutex_leave(mutex);
        }

        // Free the mutex
        sqlite3_mutex_free(mutex);
    }

    // Shutdown SQLite mutex subsystem
    sqlite3_shutdown();

    return 0;
}