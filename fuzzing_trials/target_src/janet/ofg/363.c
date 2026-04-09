#include <stdint.h>
#include <janet.h>

extern int janet_checkint64(Janet);

int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    if (size < sizeof(int64_t)) {
        return 0; // Not enough data to form an int64_t
    }

    // Create a Janet value from the input data
    int64_t intValue = *(const int64_t *)data;
    Janet janetValue = janet_wrap_integer(intValue);

    // Call the function-under-test
    int result = janet_checkint64(janetValue);

    // Use the result in some way (for example, print it)
    (void)result; // Suppress unused variable warning

    return 0;
}