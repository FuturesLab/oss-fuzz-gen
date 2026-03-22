#include <cstdint>
#include <cstdlib>
#include <iostream>

// Assuming the function is defined in some library
extern "C" {
    int tjPlaneHeight(int componentID, int subsample, int height);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize parameters with non-NULL values
    int componentID = 0; // Typically, 0 for Y, 1 for U, 2 for V in YUV formats
    int subsample = 1;   // Common subsampling values: 0 (4:4:4), 1 (4:2:2), 2 (4:2:0)
    int height = 1;      // Height of the image plane, must be positive

    // Call the function-under-test with initialized parameters
    int result = tjPlaneHeight(componentID, subsample, height);

    // Print the result to ensure the function is called
    std::cout << "Result: " << result << std::endl;

    return 0;
}