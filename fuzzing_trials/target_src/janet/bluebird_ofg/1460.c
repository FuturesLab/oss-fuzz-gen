#include <stdint.h>
#include "janet.h"

// Function to be used by the fuzzer
int LLVMFuzzerTestOneInput_1460(const uint8_t *data, size_t size) {
    // Initialize the Janet VM
    janet_init();

    if (size < sizeof(JanetKV)) {
        // Clean up Janet VM before returning
        janet_deinit();
        return 0;
    }

    JanetTable *table = janet_table(10);

    // Populate the table with some keys and values
    for (size_t i = 0; i < size / sizeof(JanetKV); i++) {
        Janet key = janet_wrap_number((double)data[i]);
        Janet value = janet_wrap_number((double)data[size - i - 1]);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    Janet result = janet_wrap_table(table);

    // Use the result in some way to prevent optimizations from removing the call
    (void)result;

    // Clean up Janet VM before returning
    janet_deinit();

    return 0;
}