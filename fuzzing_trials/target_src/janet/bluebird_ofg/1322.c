#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1322(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Create a Janet value
    Janet janet_value = janet_wrap_nil();

    // Ensure the data size is non-zero for valid input
    if (size > 0) {
        // Convert data to a Janet string
        Janet string_value = janet_stringv(data, size);

        // Put the string into the table with a key
        janet_table_put(table, janet_ckeywordv("key"), string_value);

        // Retrieve the value back to ensure the operation is complete
        janet_value = janet_table_get(table, janet_ckeywordv("key"));
    }

    // Use the value in some way to avoid any compiler optimizations
    (void)janet_value;

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}