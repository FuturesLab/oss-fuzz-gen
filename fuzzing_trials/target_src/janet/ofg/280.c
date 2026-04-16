#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern int janet_compare(Janet x, Janet y);

int LLVMFuzzerTestOneInput_280(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(Janet)) {
        return 0;
    }

    // Create two Janet values from the input data
    Janet x, y;

    // Ensure that the data is large enough to be interpreted as two Janet values
    x = janet_wrap_integer((int32_t)data[0]);
    y = janet_wrap_integer((int32_t)data[1]);

    // Call the function-under-test
    int result = janet_compare(x, y);

    // Use the result to prevent the compiler from optimizing away the call
    if (result == 0) {
        return 1;
    }

    return 0;
}