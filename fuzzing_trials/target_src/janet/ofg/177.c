#include <stdint.h>
#include <stddef.h>
#include <janet.h>  // Include the Janet library header

// Function-under-test
int janet_getboolean(const Janet *j, int32_t index);

// Fuzzing harness
int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a valid index
    if (size < sizeof(int32_t)) {
        return 0;
    }

    // Prepare a Janet array with at least one boolean value
    Janet booleans[2];
    booleans[0] = janet_wrap_boolean(1); // true
    booleans[1] = janet_wrap_boolean(0); // false

    // Extract an index from the input data
    // Ensure the index is within bounds of the booleans array
    int32_t index = *((int32_t *)data) % 2; // Use modulo to ensure index is 0 or 1

    // Call the function-under-test
    int result = janet_getboolean(booleans, index);

    // Use the result to prevent compiler optimizations
    (void)result;

    return 0;
}