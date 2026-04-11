#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure the input size is at least the size of an int32_t
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the input data
    int32_t input_value = 0;
    for (size_t i = 0; i < sizeof(int32_t); i++) {
        input_value |= ((int32_t)data[i]) << (8 * i);
    }

    // Initialize the Janet environment
    janet_init();

    // Ensure the input value is non-zero and meaningful
    if (input_value <= 0) {
        input_value = 1; // Ensure non-zero and positive input
    }

    // Call the function-under-test
    JanetTable *table = janet_table_weakv(input_value);

    // Perform more complex operations on the table
    if (table) {
        // Insert multiple dummy values to ensure the table is being used
        for (int i = 0; i < input_value; i++) {
            Janet key = janet_wrap_integer(i);
            Janet value = janet_wrap_string(janet_cstring("test"));
            janet_table_put(table, key, value);
        }

        // Perform additional operations to test different code paths
        for (int i = 0; i < input_value; i++) {
            Janet key = janet_wrap_integer(i);
            Janet retrieved_value = janet_table_get(table, key);
            if (!janet_checktype(retrieved_value, JANET_NIL)) {
                // Modify the retrieved value
                Janet new_value = janet_wrap_integer(i * 2);
                janet_table_put(table, key, new_value);
            }
        }

        // Delete some keys to test the table's handling of deletions
        for (int i = 0; i < input_value / 2; i++) {
            Janet key = janet_wrap_integer(i);
            janet_table_remove(table, key);
        }
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}