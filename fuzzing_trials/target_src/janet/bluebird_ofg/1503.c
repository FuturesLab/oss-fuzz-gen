#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

// Initialize a JanetTable with some default values
JanetTable* initialize_table_1503() {
    JanetTable *table = janet_table(10); // Create a table with an initial capacity
    // Add some dummy values to the table
    Janet key1 = janet_wrap_integer(1);
    Janet value1 = janet_wrap_integer(100);
    janet_table_put(table, key1, value1);

    Janet key2 = janet_wrap_integer(2);
    Janet value2 = janet_wrap_integer(200);
    janet_table_put(table, key2, value2);

    return table;
}

int LLVMFuzzerTestOneInput_1503(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Initialize two JanetTables
    JanetTable *table1 = initialize_table_1503();
    JanetTable *table2 = janet_table(10); // Create an empty table for fuzzing

    // Ensure the tables are not null before proceeding
    if (table1 && table2 && size > 0) {
        // Use the fuzzer input to modify the table
        for (size_t i = 0; i < size; i++) {
            Janet key = janet_wrap_integer(i);
            Janet value = janet_wrap_integer(data[i]);
            janet_table_put(table2, key, value);
        }

        // Call the function under test
        janet_table_merge_table(table1, table2);
    }

    // No need to manually deinitialize the tables, Janet's GC will handle it

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}