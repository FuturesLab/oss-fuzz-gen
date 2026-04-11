#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1336(const uint8_t *data, size_t size) {
    JanetTable *table;
    JanetTable *result;

    // Initialize the Janet environment
    janet_init();

    // Create a new JanetTable
    table = janet_table(10);

    // Ensure that the table is not NULL
    if (table == NULL) {
        janet_deinit();
        return 0;
    }

    // Populate the table with some dummy data based on the input
    for (size_t i = 0; i < size; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(data[i]);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    result = janet_core_lookup_table(table);

    // Clean up
    janet_deinit();

    return 0;
}