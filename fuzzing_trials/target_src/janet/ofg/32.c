#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <limits.h> // Include for INT32_MAX

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the input data
    int32_t table_size = *(const int32_t *)data;

    // Ensure the table size is a positive value and within a reasonable range
    if (table_size <= 0 || table_size > 1000) { // Limiting the size to a reasonable number
        return 0;
    }

    // Call the function-under-test
    JanetTable *table = janet_table(table_size);

    if (table == NULL) {
        return 0; // Handle the case where table creation fails
    }

    // Optionally, you can perform additional operations on the table
    // to increase code coverage, but ensure that no operations
    // cause undefined behavior or require specific state.

    // Clean up or further processing can be done here if needed

    return 0;
}