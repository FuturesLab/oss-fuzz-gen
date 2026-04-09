#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a Janet object
    if (size < sizeof(double)) {
        return 0;
    }

    // Create a Janet object from the input data
    // For simplicity, interpret the input data as a double
    double number;
    memcpy(&number, data, sizeof(double));
    Janet janet_number = janet_wrap_number(number);

    // Call the function-under-test
    double result = janet_unwrap_number(janet_number);

    // Optionally, you can perform some checks or operations with the result
    (void)result; // Suppress unused variable warning

    return 0;
}