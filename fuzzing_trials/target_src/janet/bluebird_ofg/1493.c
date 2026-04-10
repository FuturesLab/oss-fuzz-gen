#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1493(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Ensure we have enough data to create a JanetStruct and a Janet
    if (size < 3) { // We need at least 3 bytes to proceed
        janet_deinit();
        return 0;
    }

    // Create a Janet array to simulate a struct with at least one key-value pair
    JanetKV kvs[1];
    kvs[0].key = janet_wrap_integer(data[0]);  // Use the first byte as an integer key
    kvs[0].value = janet_wrap_integer(data[1]); // Use the second byte as an integer value

    // Begin the struct with the count of key-value pairs
    JanetKV *struct_kvs = janet_struct_begin(1);
    struct_kvs[0] = kvs[0];

    // Create a JanetStruct with the kvs array
    JanetStruct janet_struct = janet_struct_end(struct_kvs);

    // Create a Janet value for the key
    Janet key = janet_wrap_integer(data[2]); // Use the third byte as an integer for the key

    // Call the function-under-test
    Janet result = janet_struct_get(janet_struct, key);

    // Clean up and finalize Janet environment
    janet_deinit();

    return 0;
}