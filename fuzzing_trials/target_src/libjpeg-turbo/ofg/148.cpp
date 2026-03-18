#include <cstdint>
#include <cstdio>

extern "C" {
    // Declaration of the function-under-test
    int tj3YUVPlaneHeight(int componentID, int imageHeight, int subsampling);
}

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    int componentID = 0;
    int imageHeight = 1;
    int subsampling = 0;

    // Ensure the data size is sufficient for our needs
    if (size >= 3) {
        // Use the input data to set the parameters
        componentID = data[0] % 4;  // Assuming 4 possible component IDs
        imageHeight = data[1] + 1;  // Ensure imageHeight is at least 1
        subsampling = data[2] % 4;  // Assuming 4 possible subsampling values
    }

    // Call the function-under-test
    int result = tj3YUVPlaneHeight(componentID, imageHeight, subsampling);

    // Optionally, print the result for debugging purposes
    printf("Result: %d\n", result);

    return 0;
}