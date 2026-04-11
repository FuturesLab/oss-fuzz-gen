#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int64_t janet_getinteger64(const Janet *array, int32_t index);

int LLVMFuzzerTestOneInput_315(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet) + sizeof(int32_t)) {
        return 0;
    }

    // Initialize a Janet array from the input data
    Janet janetArray[1];
    janetArray[0] = janet_wrap_integer((int32_t)data[0]);

    // Extract an int32_t index from the input data
    int32_t index = (int32_t)data[sizeof(Janet)];

    // Call the function-under-test
    int64_t result = janet_getinteger64(janetArray, index);

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    return 0;
}