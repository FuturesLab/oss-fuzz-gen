#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function-under-test
int janet_compare(Janet a, Janet b);

int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create two Janet values
    if (size < 2 * sizeof(Janet)) {
        return 0;
    }

    // Create two Janet values from the input data
    Janet a = janet_wrap_integer((int)(data[0])); // Wrap the first byte as an integer
    Janet b = janet_wrap_integer((int)(data[1])); // Wrap the second byte as an integer

    // Call the function-under-test
    int result = janet_compare(a, b);

    // Use the result in some way to avoid compiler optimizations
    if (result == 0) {
        // Do something if a and b are considered equal
    }

    return 0;
}