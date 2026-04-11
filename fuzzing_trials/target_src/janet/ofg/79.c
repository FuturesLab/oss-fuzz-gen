#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy
#include <janet.h>

// Declare the external function
extern JanetFunction * janet_optfunction(const Janet *, int32_t, int32_t, JanetFunction *);

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Check if there is enough data for all parameters
    if (size < sizeof(Janet) + sizeof(int32_t) * 2 + sizeof(JanetFunction *)) {
        return 0; // Not enough data to fill all parameters
    }

    // Initialize parameters for janet_optfunction
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet)); // Safely copy data into Janet

    int32_t n;
    memcpy(&n, data + sizeof(Janet), sizeof(int32_t)); // Safely copy data into n

    int32_t def;
    memcpy(&def, data + sizeof(Janet) + sizeof(int32_t), sizeof(int32_t)); // Safely copy data into def

    JanetFunction *def_function;
    memcpy(&def_function, data + sizeof(Janet) + sizeof(int32_t) * 2, sizeof(JanetFunction *)); // Safely copy pointer

    // Check if the Janet value is a valid Janet type
    if (!janet_checktype(janet_value, JANET_FUNCTION)) {
        return 0; // If not a function, return early
    }

    // Call the function-under-test
    JanetFunction *result = janet_optfunction(&janet_value, n, def, def_function);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}