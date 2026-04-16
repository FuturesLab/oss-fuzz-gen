#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure size is sufficient to create a Janet key
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create a Janet key from the input data
    Janet key = janet_wrap_number((double)data[0]);

    // Insert the key into the table with a dummy value
    janet_table_put(table, key, janet_wrap_nil());

    // Call the function-under-test
    Janet result = janet_table_remove(table, key);

    // Clean up
    janet_deinit();

    return 0;
}