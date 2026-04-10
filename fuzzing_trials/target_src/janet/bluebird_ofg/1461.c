#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1461(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Create a new JanetTable
    JanetTable *table = janet_table(10);

    // Populate the table with some dummy data
    if (size > 0) {
        Janet key = janet_wrap_integer(data[0]);
        Janet value = janet_wrap_integer(data[0] + 1);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    Janet result = janet_wrap_table(table);

    // Use the result in some way to prevent optimization out
    if (janet_checktype(result, JANET_TABLE)) {
        // Do something with the result (e.g., print or log)
        // This is just to ensure the result is used
        janet_table_put(table, janet_wrap_integer(42), result);
    }

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}