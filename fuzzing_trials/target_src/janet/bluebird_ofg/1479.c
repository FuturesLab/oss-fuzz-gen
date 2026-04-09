#include <stdint.h>
#include <stdlib.h>
#include "janet.h"

// Initialize the Janet environment
void initialize_janet_1479() {
    janet_init();
}

// Function to create a Janet struct from data
JanetStruct create_janet_struct(const uint8_t *data, size_t size) {
    // Ensure the size is a multiple of 2 for key-value pairs
    size_t kv_count = size / 2;
    JanetKV *kvs = (JanetKV *)malloc(kv_count * sizeof(JanetKV));

    // Initialize the JanetKV pairs
    for (size_t i = 0; i < kv_count; i++) {
        kvs[i].key = janet_wrap_number(data[i * 2]);     // Example key
        kvs[i].value = janet_wrap_number(data[i * 2 + 1]); // Example value
    }

    // Correctly create a Janet struct
    JanetStruct jstruct = janet_struct_begin(kv_count);
    for (size_t i = 0; i < kv_count; i++) {
        janet_struct_put(jstruct, kvs[i].key, kvs[i].value);
    }
    janet_struct_end(jstruct);

    free(kvs);
    return jstruct;
}

int LLVMFuzzerTestOneInput_1479(const uint8_t *data, size_t size) {
    // Initialize the Janet environment if not already initialized
    static int janet_initialized = 0;
    if (!janet_initialized) {
        initialize_janet_1479();
        janet_initialized = 1;
    }

    // Ensure that the size is sufficient to create at least one key-value pair
    if (size < 2) {
        return 0;
    }

    // Create a Janet struct from the input data
    JanetStruct jstruct = create_janet_struct(data, size);

    // Convert the Janet struct to a table
    JanetTable *table = janet_struct_to_table(jstruct);

    // Clean up if necessary (depends on Janet API usage)
    // No explicit free needed for table as per Janet API

    return 0;
}