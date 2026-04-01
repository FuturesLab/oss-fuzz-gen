#include <cstdint>
#include <cstdlib>

// Assume the function-under-test is declared somewhere
extern "C" {
    int tj3YUVPlaneHeight(int componentID, int subsamp, int height);
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0] % 3); // Assuming 3 components (e.g., Y, U, V)
    int subsamp = static_cast<int>(data[1] % 5);     // Assuming 5 subsampling options
    int height = static_cast<int>(data[2] % 1000) + 1; // Height should be positive

    // Call the function-under-test
    int result = tj3YUVPlaneHeight(componentID, subsamp, height);

    // Use the result in some way to avoid compiler optimizations
    volatile int sink = result;
    (void)sink;

    return 0;
}