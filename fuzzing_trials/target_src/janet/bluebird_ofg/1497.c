#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1497(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create Janet values
    if (size < 3 * sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Create a JanetKV structure
    JanetKV *kv = janet_struct_begin(1);

    // Extract Janet values from the input data
    Janet key = janet_wrap_integer(((int32_t *)data)[0]);
    Janet value = janet_wrap_integer(((int32_t *)data)[1]);
    Janet another_value = janet_wrap_integer(((int32_t *)data)[2]);

    // Call the function-under-test
    janet_struct_put(kv, key, value);

    // Optionally, add another value to test different scenarios
    janet_struct_put(kv, key, another_value);

    // Finalize the JanetKV structure
    JanetStruct final_struct = janet_struct_end(kv);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}