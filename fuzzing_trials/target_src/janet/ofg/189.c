#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function signature to be fuzzed
int janet_checkint(Janet);

// Fuzzing harness for janet_checkint
int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a Janet type
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Create a Janet value from the input data
    int32_t intValue;
    memcpy(&intValue, data, sizeof(int32_t));
    Janet janetValue = janet_wrap_integer(intValue);

    // Call the function-under-test
    int result = janet_checkint(janetValue);

    // Use result to avoid compiler optimizations
    (void)result;

    return 0;
}