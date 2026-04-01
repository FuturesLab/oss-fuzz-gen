#include <stdint.h>
#include <stddef.h> // Include this for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_375(const uint8_t *data, size_t size) {
    // Declare and initialize the parameter for sqlite3_sleep
    int ms = 1; // Initialize with a non-zero value to avoid a no-op

    // Call the function-under-test
    sqlite3_sleep(ms);

    return 0;
}