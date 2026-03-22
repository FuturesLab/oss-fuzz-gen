#include <cstdint>
#include <cstdlib>

// Assuming tj3YUVPlaneWidth is defined in an external C library
extern "C" {
    int tj3YUVPlaneWidth(int componentID, int width, int subsampling);
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data to extract three integers
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0]);
    int width = static_cast<int>(data[1]);
    int subsampling = static_cast<int>(data[2]);

    // Call the function-under-test
    int result = tj3YUVPlaneWidth(componentID, width, subsampling);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result; // In this case, we simply cast to void

    return 0;
}