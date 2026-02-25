#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    // Include the necessary header for the function under test
    #include "aom/aom_codec.h" // Adjust the path according to your project structure
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure that the input size is valid and not too large
    if (size == 0 || size > 1024) {
        return 0; // Skip invalid inputs
    }

    // Prepare variables for the function call
    uint64_t decoded_value = 0;
    size_t bytes_read = 0;

    // Call the function under test
    int result = aom_uleb_decode(data, size, &decoded_value, &bytes_read);

    // Optionally, you can check the result or decoded value here
    // For example, you could log or assert something based on the result

    return 0; // Return 0 to indicate successful execution
}