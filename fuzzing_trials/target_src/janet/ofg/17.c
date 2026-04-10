#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Ensure there is enough data to create a Janet object
    if (size < sizeof(int16_t)) {
        return 0;
    }

    // Use the data to create a Janet integer
    int16_t value = (int16_t)(data[0] | (data[1] << 8));
    Janet janet_value = janet_wrap_integer(value);

    // Call the function-under-test
    int result = janet_checkint16(janet_value);

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}