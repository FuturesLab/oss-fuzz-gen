#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <janet.h>   // Include for JanetTable and related functions

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a 32-bit integer
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t from the input data
    int32_t capacity;
    memcpy(&capacity, data, sizeof(int32_t));

    // Ensure capacity is positive and within a reasonable range
    if (capacity <= 0 || capacity > 10000) {
        return 0;
    }

    // Initialize a JanetTable
    JanetTable table;

    // Call the function-under-test
    JanetTable *result = janet_table_init_raw(&table, capacity);

    // Ensure result is not NULL
    if (result == NULL) {
        return 0;
    }

    // Optionally, perform further operations on the result if needed
    // For example, insert some dummy data to ensure the table is functional
    for (int i = 0; i < capacity; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(i * 2);
        janet_table_put(result, key, value);
    }

    // Verify the table's content
    for (int i = 0; i < capacity; i++) {
        Janet key = janet_wrap_integer(i);
        Janet expected_value = janet_wrap_integer(i * 2);
        Janet actual_value = janet_table_get(result, key);
        if (!janet_equals(expected_value, actual_value)) {
            return 0;
        }
    }

    return 0;
}