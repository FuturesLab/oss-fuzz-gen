#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Create a new JanetTable
    JanetTable *table = janet_table(10);

    // Ensure that the size is sufficient to extract two Janet values
    if (size < 2 * sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Extract two Janet values from the input data
    Janet key = janet_wrap_integer(data[0]);
    Janet value = janet_wrap_integer(data[1]);

    // Call the function-under-test
    janet_table_put(table, key, value);

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}