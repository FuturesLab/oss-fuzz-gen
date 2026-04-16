#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_345(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t) + sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Extract parameters from data
    Janet array = *(const Janet *)data;
    int32_t index = *(const int32_t *)(data + sizeof(Janet));
    Janet value = *(const Janet *)(data + sizeof(Janet) + sizeof(int32_t));

    // Ensure the Janet array is valid
    if (!janet_checktype(array, JANET_ARRAY)) {
        array = janet_wrap_array(janet_array(10)); // Create a default array
    }

    // Call the function-under-test
    janet_putindex(array, index, value);

    // Clean up
    janet_deinit();

    return 0;
}