#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1418(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Create a new JanetTable
    JanetTable *table = janet_table(10);

    // Populate the table with some data from the fuzzer input
    for (size_t i = 0; i < size; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(data[i]);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    JanetStruct result = janet_table_to_struct(table);

    // Clean up
    janet_deinit();

    return 0;
}