#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    sqlite3_mutex *mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);

    if (mutex != NULL) { // NULL is defined in stddef.h
        // Call the function-under-test
        int result = sqlite3_mutex_notheld(mutex);

        // Free the allocated mutex
        sqlite3_mutex_free(mutex);
    }

    return 0;
}