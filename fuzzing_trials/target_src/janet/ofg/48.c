#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Create a Janet object from the input data
    Janet janet_value = janet_wrap_integer(*(const uint64_t *)data);

    // Call the function-under-test
    int result = janet_checkuint(janet_value);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}