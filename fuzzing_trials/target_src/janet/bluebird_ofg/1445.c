#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1445(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure the data size is sufficient to create a Janet key
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Use the data to create a Janet key
    Janet key = janet_wrap_string(janet_string(data, size));

    // Insert the key into the table with a dummy value
    janet_table_put(table, key, janet_wrap_nil());

    // Call the function-under-test
    JanetKV *result = janet_table_find(table, key);

    // Check the result to ensure it's not NULL
    if (result != NULL) {
        // Optionally, perform additional checks or operations on the result
    }

    // Clean up
    janet_deinit();

    return 0;
}