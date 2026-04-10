#include <stdint.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Create a Janet value from the input data
    Janet janetValue;
    if (size >= sizeof(Janet)) {
        // Use the input data to create a Janet value
        janetValue = *(Janet *)data;
    } else {
        // If the input data is not large enough to form a Janet value, return
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    JanetTuple result = janet_unwrap_tuple(janetValue);

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}