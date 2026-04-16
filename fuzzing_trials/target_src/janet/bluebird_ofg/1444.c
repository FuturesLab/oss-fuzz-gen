#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1444(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure size is sufficient for a Janet string
    if (size == 0) {
        // Deinitialize the Janet environment before returning
        janet_deinit();
        return 0;
    }

    // Create a Janet string from the input data
    const uint8_t *janet_str = janet_string((const char *)data, size);
    Janet janet_string = janet_wrap_string(janet_str);

    // Call the function-under-test
    int32_t hash_result = janet_hash(janet_string);

    // Use the hash_result to avoid compiler optimizations
    (void)hash_result;

    // Deinitialize the Janet environment before returning
    janet_deinit();

    return 0;
}