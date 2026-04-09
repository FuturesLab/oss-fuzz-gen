#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern int janet_scan_number(const uint8_t *, int32_t, double *);

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    int32_t length = (int32_t)size;
    double result = 0.0;

    // Call the function-under-test
    janet_scan_number(data, length, &result);

    return 0;
}