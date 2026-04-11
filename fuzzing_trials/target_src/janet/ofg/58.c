#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure that data is not empty
    if (size < 1) {
        janet_deinit();
        return 0;
    }

    // Use the first byte of data as a key and the rest as a value
    Janet key = janet_wrap_integer(data[0]);
    Janet value = janet_wrap_string(janet_string(data + 1, size - 1));

    // Put the key-value pair in the table
    janet_table_put(table, key, value);

    // Call the function-under-test
    Janet result = janet_table_remove(table, key);

    // Clean up
    janet_deinit();

    return 0;
}