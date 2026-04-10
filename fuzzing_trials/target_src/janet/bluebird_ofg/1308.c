#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1308(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a Janet object and an int32_t
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize the Janet VM
    janet_init();

    // Initialize a Janet object from the data
    Janet janet_obj;
    // Properly initialize the Janet object to prevent undefined behavior
    janet_obj = janet_wrap_nil(); // Initialize with a default value

    // Copy data into the Janet object
    // Note: Ensure that the data is compatible with the expected Janet type
    memcpy(&janet_obj, data, sizeof(Janet));

    // Initialize an int32_t index from the data
    int32_t index;
    memcpy(&index, data + sizeof(Janet), sizeof(int32_t));

    // Call the function-under-test
    uint64_t result = 0;
    if (janet_checktype(janet_obj, JANET_NUMBER)) {
        // Create an array of Janet objects to pass to janet_getuinteger64
        Janet argv[1];
        argv[0] = janet_obj;
        // Ensure the index is within bounds
        if (index >= 0 && index < 1) {
            // Only call the function if the Janet object is a number
            result = janet_getuinteger64(argv, index);
        }
    }

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    // Clean up the Janet VM
    janet_deinit();

    return 0;
}