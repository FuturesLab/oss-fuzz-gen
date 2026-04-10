#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_386(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Create a Janet value from the input data
    Janet janet_value = janet_wrap_number((double)data[0]);

    // Call the function-under-test
    JanetSymbol result = janet_unwrap_symbol(janet_value);

    // Use the result to avoid compiler optimizations removing the call
    (void)result;

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}