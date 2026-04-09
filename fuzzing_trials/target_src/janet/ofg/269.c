#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>
#include "/src/janet/src/include/janet.h"

// Ensure that the Janet library is initialized
static void initialize_janet_269() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_269(const uint8_t *data, size_t size) {
    // Initialize Janet library
    initialize_janet_269();

    // Ensure that size is large enough to extract an int32_t
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t value from the data
    int32_t input_value;
    memcpy(&input_value, data, sizeof(int32_t));

    // Call the function-under-test with a non-negative input
    JanetTable *table = janet_table_weakk(input_value >= 0 ? input_value : 0);

    // Check if the table is null, which indicates a potential issue
    if (table == NULL) {
        return 0;
    }

    // Example operation: insert multiple key-value pairs
    for (size_t i = sizeof(int32_t); i + sizeof(int32_t) <= size; i += sizeof(int32_t)) {
        // Extract another int32_t from the data
        int32_t key_value;
        memcpy(&key_value, data + i, sizeof(int32_t));

        // Use the extracted value as both key and value for testing
        Janet key = janet_wrap_integer(key_value);
        Janet value = janet_wrap_integer(key_value + 1); // Slightly modify for diversity
        janet_table_put(table, key, value);
    }

    // Optionally, iterate over the table to further test its behavior
    const JanetKV *kv = table->data; // Access the data directly
    for (size_t j = 0; j < table->capacity; j++) { // Access the capacity directly
        if (!janet_checktype(kv[j].key, JANET_NIL)) {
            // Perform some operation with kv[j].key and kv[j].value
            (void)kv[j].key; // Example: just access the key
            (void)kv[j].value; // Example: just access the value
        }
    }

    // Additional operations to increase fuzzing effectiveness
    for (size_t i = sizeof(int32_t); i + sizeof(int32_t) <= size; i += sizeof(int32_t)) {
        int32_t key_value;
        memcpy(&key_value, data + i, sizeof(int32_t));
        Janet key = janet_wrap_integer(key_value);
        janet_table_remove(table, key); // Attempt to remove entries
    }

    // Clean up the table to prevent memory leaks
    janet_table_clear(table);

    return 0;
}