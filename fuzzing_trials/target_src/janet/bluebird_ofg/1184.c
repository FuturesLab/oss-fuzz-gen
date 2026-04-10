#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include "janet.h" // Include for Janet-related functions and types

int LLVMFuzzerTestOneInput_1184(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure that the input size is sufficient to create a JanetKV and a Janet
    if (size < sizeof(JanetKV) + sizeof(Janet)) {
        janet_deinit(); // Clean up the Janet environment before returning
        return 0;
    }

    // Initialize a JanetKV structure
    JanetKV kv;
    kv.key = janet_wrap_nil();  // Initialize key with a default value
    kv.value = janet_wrap_nil(); // Initialize value with a default value

    // Initialize a Janet value
    Janet janet_value = janet_wrap_nil(); // Initialize with default value

    // Copy data into the JanetKV and Janet structures
    // Ensure the data is not NULL
    if (data != NULL) {
        // Use the first part of data for the JanetKV
        memcpy(&kv, data, sizeof(JanetKV));

        // Use the remaining part of data for the Janet value
        if (size >= sizeof(JanetKV) + sizeof(Janet)) {
            memcpy(&janet_value, data + sizeof(JanetKV), sizeof(Janet));
        }
    }

    // Initialize a JanetStruct from the data
    // This requires allocating a JanetKV array and setting it up correctly
    size_t kv_size = size / sizeof(JanetKV);
    if (kv_size == 0) {
        janet_deinit(); // Clean up the Janet environment before returning
        return 0; // Avoid division by zero and invalid memory operations
    }
    JanetKV *kvs = (JanetKV *)malloc(kv_size * sizeof(JanetKV));
    if (!kvs) {
        janet_deinit(); // Clean up the Janet environment before returning
        return 0;
    }
    memcpy(kvs, data, kv_size * sizeof(JanetKV));
    JanetStruct janet_struct = janet_struct_begin(kv_size);
    for (size_t i = 0; i < kv_size; i++) {
        // Ensure keys and values are valid Janet types
        Janet key = janet_checktype(kvs[i].key, JANET_NIL) ? janet_wrap_nil() : kvs[i].key;
        Janet value = janet_checktype(kvs[i].value, JANET_NIL) ? janet_wrap_nil() : kvs[i].value;
        janet_struct_put(janet_struct, key, value);
    }
    janet_struct_end(janet_struct);

    // Call the function-under-test
    Janet result = janet_struct_rawget(janet_struct, janet_value);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    // Free allocated memory
    free(kvs);

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}