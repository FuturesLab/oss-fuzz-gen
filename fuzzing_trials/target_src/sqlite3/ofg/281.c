#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    int type;
    sqlite3_mutex *mutex;

    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer for the mutex type
    type = *(const int*)data;

    // Ensure the type is within a valid range for sqlite3_mutex_alloc
    // SQLite defines several mutex types, we can use a range check
    if (type < 0 || type > 8) { // Assuming 8 is the max valid type for demonstration
        return 0;
    }

    // Call the function-under-test
    mutex = sqlite3_mutex_alloc(type);

    // If a mutex is allocated, free it
    if (mutex != NULL) {
        sqlite3_mutex_free(mutex);
    }

    return 0;
}