#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create Janet values
    if (size < 2 * sizeof(Janet)) {
        return 0;
    }

    // Initialize a JanetTable
    JanetTable table;
    janet_table_init(&table, 10); // Initialize with a capacity of 10

    // Extract Janet values from the input data
    Janet key = janet_wrap_integer((int32_t)data[0]);
    Janet value = janet_wrap_integer((int32_t)data[1]);

    // Call the function-under-test
    janet_table_put(&table, key, value);

    // Clean up the table
    janet_table_deinit(&table);

    return 0;
}