#include <stdint.h>
#include <stdlib.h>
#include "janet.h" // Include the Janet library header

int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create two JanetTable objects
    JanetTable *table1 = janet_table(10); // Initial size of 10
    JanetTable *table2 = janet_table(10); // Initial size of 10

    // Populate the tables with some data from the input
    for (size_t i = 0; i < size; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(data[i]);
        janet_table_put(table1, key, value);
        janet_table_put(table2, key, value);
    }

    // Call the function-under-test
    janet_table_merge_table(table1, table2);

    // Clean up
    janet_deinit();

    return 0;
}