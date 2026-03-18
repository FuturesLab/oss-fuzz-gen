#include <cstdint>
#include <cstdlib>

// Assuming the function is defined in a C library
extern "C" {
    int tjPlaneHeight(int componentID, int width, int height);
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract integers from the input data
    int componentID = static_cast<int>(data[0]); // Use the first byte for componentID
    int width = static_cast<int>(data[1]);       // Use the second byte for width
    int height = static_cast<int>(data[2]);      // Use the third byte for height

    // Call the function-under-test
    int result = tjPlaneHeight(componentID, width, height);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}