#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

// Helper function to create a valid Janet dictionary
Janet create_valid_janet_dictionary() {
    JanetTable *table = janet_table(0);
    Janet key = janet_cstringv("key");
    Janet value = janet_cstringv("value");
    janet_table_put(table, key, value);
    return janet_wrap_table(table);
}

int LLVMFuzzerTestOneInput_1433(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Initialize the Janet environment
    janet_init();

    // Create a valid Janet dictionary
    Janet janet_value = create_valid_janet_dictionary();
    JanetTable *table = janet_unwrap_table(janet_value);
    int32_t index;

    // Copy the index from the input data
    memcpy(&index, data, sizeof(int32_t));

    // Ensure the index is within a valid range
    index = index % 2; // Since the dictionary only contains one key-value pair

    // Use a valid key to get the value from the table
    Janet key = janet_cstringv("key");
    Janet result = janet_table_get(table, key);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}