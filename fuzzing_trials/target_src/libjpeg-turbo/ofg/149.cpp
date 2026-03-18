#include <cstdint>
#include <cstdlib>

// Assuming the function is part of a library, we wrap it in extern "C" to ensure proper linkage with C++.
extern "C" {
    // Include the correct path where tj3YUVPlaneHeight is declared.
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

// Fuzzing harness for tj3YUVPlaneHeight
extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the parameters of tj3YUVPlaneHeight
    int componentID = 0;
    int width = 1;
    int subsample = 1;

    // Ensure that the size is sufficient to extract parameters
    if (size >= 3) {
        // Use the input data to set the parameters
        componentID = data[0] % 4;  // Assuming componentID can be 0 to 3
        width = data[1] + 1;        // Ensure width is at least 1
        subsample = data[2] % 4;    // Assuming subsample can be 0 to 3
    }

    // Call the function-under-test
    int result = tj3YUVPlaneHeight(componentID, width, subsample);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}