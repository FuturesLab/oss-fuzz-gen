#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include "janet.h" // Assuming the header file for JanetTable is named janet.h

// Function signature from the task
JanetTable *janet_table_init(JanetTable *table, int32_t capacity);

int LLVMFuzzerTestOneInput_373(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an int32_t value
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize a JanetTable
    JanetTable table;

    // Extract an int32_t value from the input data
    int32_t capacity;
    memcpy(&capacity, data, sizeof(int32_t));

    // Call the function-under-test
    JanetTable *result = janet_table_init(&table, capacity);

    // Use the result to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Perform some basic operations to ensure the table is used
        // This is just to ensure that the function call is not optimized away
        result->count = 0;

        // Further utilize the table to ensure it is being used
        // Attempt to insert some data into the table
        if (size > sizeof(int32_t)) {
            // Use the rest of the data as key-value pairs
            size_t remaining_size = size - sizeof(int32_t);
            const uint8_t *remaining_data = data + sizeof(int32_t);

            // Insert key-value pairs into the table
            for (size_t i = 0; i + 1 < remaining_size; i += 2) {
                Janet key = janet_wrap_integer(remaining_data[i]);
                Janet value = janet_wrap_integer(remaining_data[i + 1]);
                janet_table_put(result, key, value);
            }
        }
    }

    return 0;
}