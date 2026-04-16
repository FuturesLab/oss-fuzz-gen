#include "janet.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_1420(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a key and value
    if (size < 2 * sizeof(int32_t)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a JanetTable with initial capacity
    JanetTable *table = janet_table(10);
    Janet key;
    Janet value;
    JanetTable *found_table = NULL;

    // Initialize key and value from the input data
    key = janet_wrap_integer((int32_t)data[0]);
    value = janet_wrap_integer((int32_t)data[1]);

    // Put the key-value pair into the table
    janet_table_put(table, key, value);

    // Call the function-under-test
    Janet result = janet_table_get_ex(table, key, &found_table);

    // Use the result and found_table in some way to avoid compiler optimizations
    if (janet_checktype(result, JANET_NIL) && found_table == NULL) {
        // Do something trivial
    }

    // Cleanup
    janet_deinit();

    return 0;
}