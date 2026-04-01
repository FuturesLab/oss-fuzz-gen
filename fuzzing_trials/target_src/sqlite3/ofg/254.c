#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_mutex object
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
    
    // Ensure the mutex is not NULL before proceeding
    if (mutex != NULL) {
        // Call the function-under-test
        sqlite3_mutex_free(mutex);
    }

    return 0;
}