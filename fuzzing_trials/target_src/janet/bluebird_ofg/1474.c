#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1474(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Initialize a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure the table is not NULL
    if (table == NULL) {
        janet_deinit(); // Deinitialize the Janet runtime
        return 0;
    }

    // Fill the table with some data based on input
    for (size_t i = 0; i < size; i++) {
        // Use the data to insert into the table
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(data[i]);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    janet_table_clear(table);

    // Clean up
    // Remove janet_table_deinit and free(table) as janet_table_clear handles cleanup
    // janet_table_deinit(table);
    // free(table);

    // Deinitialize the Janet runtime
    janet_deinit();

    return 0;
}