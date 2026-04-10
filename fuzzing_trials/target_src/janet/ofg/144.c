#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Create a Janet key and value
    Janet key = janet_wrap_integer(42); // Using a fixed integer for simplicity
    Janet value = janet_wrap_string(janet_cstring("value"));

    // Put the key-value pair into the table
    janet_table_put(table, key, value);

    // Use the data as a key to get a value from the table, if possible
    if (size >= sizeof(Janet)) {
        Janet input_key = janet_wrap_integer((int32_t)data[0]); // Simple conversion for fuzzing
        Janet result = janet_table_get(table, input_key);
        
        // Use the result in some way to avoid optimizing it out
        if (janet_checktype(result, JANET_NIL)) {
            // Do nothing if result is nil
        } else {
            // Use the result if it's not nil
            janet_unwrap_string(result);
        }
    }

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}