#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_334(const uint8_t *data, size_t size) {
    Janet arg1, arg2;
    Janet result;

    // Initialize Janet VM
    janet_init();

    // Ensure the data size is sufficient for two Janet values
    if (size < 2 * sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Create two Janet values from the input data
    arg1 = janet_wrap_integer((int64_t)data[0]);
    arg2 = janet_wrap_integer((int64_t)data[1]);

    // Call the function-under-test
    result = janet_in(arg1, arg2);

    // Clean up Janet VM
    janet_deinit();

    return 0;
}