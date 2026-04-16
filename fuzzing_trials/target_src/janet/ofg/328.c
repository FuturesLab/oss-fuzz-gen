#include <stdint.h>
#include <stddef.h>

// Assume janet.h provides the declaration for janet_init()
#include <janet.h>

int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int result = janet_init();

    // Since janet_init() does not take any parameters, we do not use `data` or `size`
    // in this fuzzing harness. However, we must call the function to test it.

    (void)data; // Suppress unused variable warning
    (void)size; // Suppress unused variable warning

    return result;
}