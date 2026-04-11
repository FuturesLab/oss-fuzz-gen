#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern Janet janet_wrap_number_safe(double);

int LLVMFuzzerTestOneInput_260(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    // Extract a double value from the input data
    double num;
    memcpy(&num, data, sizeof(double));

    // Call the function-under-test
    Janet result = janet_wrap_number_safe(num);

    // Use the result in some way (e.g., just to avoid unused variable warnings)
    (void)result;

    return 0;
}