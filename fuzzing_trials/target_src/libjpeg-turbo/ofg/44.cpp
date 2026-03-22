#include <cstdint>
#include <cstdlib>

// Assuming tj3YUVPlaneHeight is declared in an external C library
extern "C" {
    int tj3YUVPlaneHeight(int componentID, int width, int subsampling);
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract integers from the input data
    int componentID = static_cast<int>(data[0]); // Using first byte for componentID
    int width = static_cast<int>(data[1]);       // Using second byte for width
    int subsampling = static_cast<int>(data[2]); // Using third byte for subsampling

    // Call the function-under-test with the extracted values
    tj3YUVPlaneHeight(componentID, width, subsampling);

    return 0;
}