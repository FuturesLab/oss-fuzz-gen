#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this for memcpy
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Extract an integer from the input data
    int mutex_type;
    memcpy(&mutex_type, data, sizeof(int));

    // Call the function-under-test
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(mutex_type);

    // If a mutex was allocated, free it
    if (mutex != NULL) {
        sqlite3_mutex_free(mutex);
    }

    // Shutdown SQLite
    sqlite3_shutdown();

    return 0;
}