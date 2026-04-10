#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet object from the input data
    Janet janet_value = janet_wrap_number(*(const double *)data);

    // Call the function-under-test
    int result = janet_checkuint64(janet_value);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}