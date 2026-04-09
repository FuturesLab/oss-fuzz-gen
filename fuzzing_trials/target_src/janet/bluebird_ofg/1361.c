#include <stdint.h>
#include <stddef.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_1361(const uint8_t *data, size_t size) {
    // Initialize the Janet environment
    janet_init();

    // Ensure that size is a multiple of the size of Janet
    if (size % sizeof(Janet) != 0 || size == 0) {
        janet_deinit();
        return 0;
    }

    // Calculate the number of Janet elements
    int32_t num_elements = size / sizeof(Janet);

    // Cast the data to an array of Janet
    const Janet *janet_array = (const Janet *)data;

    // Call the function-under-test
    JanetTuple result = janet_tuple_n(janet_array, num_elements);

    // Use the result in some way to avoid unused variable warnings
    if (result) {
        // Do something with result if necessary
    }

    // Deinitialize the Janet environment
    janet_deinit();

    return 0;
}