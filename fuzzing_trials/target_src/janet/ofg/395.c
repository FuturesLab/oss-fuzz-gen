#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_395(const uint8_t *data, size_t size) {
    // Initialize Janet VM
    janet_init();

    // Ensure there's enough data to create two Janet objects
    if (size < 2 * sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create two Janet objects from the input data
    Janet janet1 = janet_wrap_integer((int32_t)data[0]);
    Janet janet2 = janet_wrap_integer((int32_t)data[1]);

    // Call the function-under-test
    Janet result = janet_next(janet1, janet2);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}