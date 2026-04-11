#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h> // Ensure the Janet library is included

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a Janet type
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Interpret the input data as a Janet type
    Janet janet_input;
    memcpy(&janet_input, data, sizeof(Janet));

    // Ensure the Janet environment is initialized
    janet_init();

    // Call the function-under-test using the macro
    int result = janet_truthy(janet_input);

    // Use result in some way to avoid compiler optimizations
    (void)result;

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}