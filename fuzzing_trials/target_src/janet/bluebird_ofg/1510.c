#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1510(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure that the data is large enough to create a Janet key
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet key from the input data
    Janet key = janet_wrap_number((double)data[0]);

    // Populate the table with some values
    for (int i = 0; i < 10; i++) {
        Janet key = janet_wrap_number((double)i);
        Janet value = janet_wrap_number((double)(i * 2));
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    Janet result = janet_table_rawget(table, key);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}