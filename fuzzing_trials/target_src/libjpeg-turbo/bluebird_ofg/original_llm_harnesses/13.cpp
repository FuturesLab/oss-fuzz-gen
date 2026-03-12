#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
// Declaration of the function-under-test
int tj3YUVPlaneWidth(int componentID, int width, int align);
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract three integers
    if (size < 3 * sizeof(int)) {
        return 0;
    }

    // Extract three integers from the input data
    int componentID = static_cast<int>(data[0]);
    int width = static_cast<int>(data[1]);
    int align = static_cast<int>(data[2]);

    // Call the function-under-test
    int result = tj3YUVPlaneWidth(componentID, width, align);

    // Print the result (optional, for debugging purposes)
    printf("tj3YUVPlaneWidth(%d, %d, %d) = %d\n", componentID, width, align, result);

    return 0;
}