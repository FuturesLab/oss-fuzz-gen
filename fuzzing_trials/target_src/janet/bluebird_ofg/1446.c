#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

// Function to initialize a JanetTable with some data
JanetTable *initialize_table_1446() {
    JanetTable *table = janet_table(10); // Create a table with initial size 10

    // Add some key-value pairs to the table
    Janet key1 = janet_wrap_string(janet_cstring("key1"));
    Janet value1 = janet_wrap_integer(42);
    janet_table_put(table, key1, value1);

    Janet key2 = janet_wrap_string(janet_cstring("key2"));
    Janet value2 = janet_wrap_integer(84);
    janet_table_put(table, key2, value2);

    return table;
}

int LLVMFuzzerTestOneInput_1446(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Initialize a JanetTable
    JanetTable *original_table = initialize_table_1446();

    // Ensure that the data is not null and has a reasonable size
    if (size > 0) {
        // Create a string from the input data
        char *input_string = (char *)malloc(size + 1);
        if (!input_string) {
            janet_deinit();
            return 0; // Exit if memory allocation fails
        }
        memcpy(input_string, data, size);
        input_string[size] = '\0';

        // Use the input string as a key in the table
        Janet key = janet_wrap_string(janet_cstring(input_string));
        Janet value = janet_wrap_integer(100); // Arbitrary value
        janet_table_put(original_table, key, value);

        free(input_string);
    }

    // Call the function-under-test
    JanetTable *cloned_table = janet_table_clone(original_table);

    // Clean up
    janet_deinit(); // Deinitialize the Janet environment

    return 0;
}