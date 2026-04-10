#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Initialize Janet VM
void initialize_janet_335() {
    static int janet_initialized = 0;
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_335(const uint8_t *data, size_t size) {
    // Initialize Janet
    initialize_janet_335();

    // Create two Janet objects from the input data
    Janet x, y;

    if (size >= 2) {
        x = janet_wrap_integer((int32_t)data[0]);
        y = janet_wrap_integer((int32_t)data[1]);
    } else {
        x = janet_wrap_integer(0);
        y = janet_wrap_integer(0);
    }

    // Call the function-under-test
    Janet result = janet_in(x, y);

    // Use the result to prevent compiler optimizations
    (void)result;

    return 0;
}