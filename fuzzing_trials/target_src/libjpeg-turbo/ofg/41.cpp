#include <cstdint>
#include <cstdlib>
#include <cstdio>

// Assuming the function is declared in an external C library
extern "C" {
    int tj3YUVPlaneWidth(int componentID, int width, int subsampling);
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract integers from the input data
    int componentID = static_cast<int>(data[0] % 3); // Assuming componentID is between 0 and 2
    int width = static_cast<int>(data[1]) + 1; // Ensure width is non-zero
    int subsampling = static_cast<int>(data[2] % 4); // Assuming subsampling is between 0 and 3

    // Call the function-under-test
    int result = tj3YUVPlaneWidth(componentID, width, subsampling);

    // Print the result (optional, for debugging purposes)
    printf("Result: %d\n", result);

    return 0;
}