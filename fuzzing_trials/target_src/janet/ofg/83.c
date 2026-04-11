#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an int32_t index
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Extract an int32_t index from the data
    int32_t index = *((int32_t *)data);

    // Ensure the index is within a valid range for the Janet array
    // Since we are only creating an array with one element, the only valid index is 0
    if (index != 0) {
        return 0;
    }

    // Prepare a Janet array with at least one element
    Janet janetArray[1];
    janetArray[0] = janet_wrap_string(janet_string(data + sizeof(int32_t), size - sizeof(int32_t)));

    // Call the function-under-test
    JanetString result = janet_getstring(janetArray, index);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        // Do something with the result, e.g., print its length
        size_t length = janet_string_length(result);
        (void)length; // Suppress unused variable warning
    }

    return 0;
}