#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Check if the input data is not null and size is greater than zero
    if (data == NULL || size == 0) {
        return 0; // No processing for null or empty input
    }

    // Call the function-under-test
    Janet result = janet_wrap_true();

    // Use the result in some way to prevent the compiler from optimizing it away
    if (janet_truthy(result)) {
        // Do nothing, just a placeholder to use the result
    }

    return 0;
}