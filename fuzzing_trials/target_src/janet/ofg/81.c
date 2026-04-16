#include <janet.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Ensure size is sufficient for creating a Janet string
    if (size == 0) {
        return 0;
    }

    // Create a Janet string from the input data
    Janet janet_value = janet_stringv((const uint8_t *)data, size);

    // Call the function-under-test
    JanetStruct result = janet_unwrap_struct(janet_value);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}