#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure that the size is at least 8 bytes to extract two int32_t values
    if (size < 2 * sizeof(int32_t)) {
        janet_deinit();
        return 0;
    }

    // Extract two int32_t values from the input data
    int32_t input_value1, input_value2;
    memcpy(&input_value1, data, sizeof(int32_t));
    memcpy(&input_value2, data + sizeof(int32_t), sizeof(int32_t));

    // Ensure the input values are non-negative to avoid potential issues
    if (input_value1 < 0 || input_value2 < 0) {
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    JanetTable *table = janet_table(input_value1);

    // Check if the table was created successfully
    if (table == NULL) {
        janet_deinit();
        return 0;
    }

    // Perform operations on the table
    // Insert a key-value pair into the table
    Janet key = janet_wrap_integer(input_value1);
    Janet value = janet_wrap_integer(input_value2);
    janet_table_put(table, key, value);

    // Retrieve the value using the key
    Janet retrieved_value = janet_table_get(table, key);

    // Ensure the retrieved value matches the inserted value
    if (!janet_equals(retrieved_value, value)) {
        janet_deinit();
        return 0;
    }

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}