#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Ensure the input data is interpreted as a double
    double num;
    memcpy(&num, data, sizeof(double));

    // Call the function-under-test
    Janet result = janet_wrap_number(num);

    // Optionally, use the result in some way to avoid compiler optimizations
    // that might skip the function call. Here, we just print it.
    (void)result; // To suppress unused variable warning

    return 0;
}