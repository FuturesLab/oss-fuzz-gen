#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Declare the function prototype for janet_optnumber
double janet_optnumber(const Janet *array, int32_t len, int32_t n, double def);

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract required parameters
    if (size < sizeof(Janet) + 2 * sizeof(int32_t) + sizeof(double)) {
        return 0;
    }

    // Initialize the parameters for janet_optnumber
    const Janet *janetArray = (const Janet *)data;
    int32_t len = (int32_t)(size / sizeof(Janet));
    int32_t n = (int32_t)data[sizeof(Janet)];
    double def = *((double *)(data + sizeof(Janet) + sizeof(int32_t)));

    // Call the function-under-test
    double result = janet_optnumber(janetArray, len, n, def);

    // Use the result in some way to avoid compiler optimizations
    if (result == 0.0) {
        return 1;
    }

    return 0;
}