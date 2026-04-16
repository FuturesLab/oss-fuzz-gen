#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    if (size < sizeof(int16_t)) {
        return 0;
    }

    // Initialize Janet
    janet_init();

    // Create a Janet object from the input data
    Janet janet_value;
    int16_t value = *((int16_t *)data);
    janet_value = janet_wrap_integer(value);

    // Call the function-under-test
    int result = janet_checkint16(janet_value);

    // Clean up Janet
    janet_deinit();

    return 0;
}