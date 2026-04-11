#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_259(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0;
    }

    double number;
    memcpy(&number, data, sizeof(double));

    Janet result = janet_wrap_number_safe(number);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}