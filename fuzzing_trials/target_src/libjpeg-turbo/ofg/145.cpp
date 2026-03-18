#include <cstdint>
#include <cstdlib>
#include <iostream>

// Include the necessary header for tjPlaneSizeYUV if available
extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

// Define the LLVMFuzzerTestOneInput function
extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract parameters
    if (size < 5 * sizeof(int)) {
        return 0;
    }

    // Extract parameters from the input data
    int width = static_cast<int>(data[0]);
    int height = static_cast<int>(data[1]);
    int subsamp = static_cast<int>(data[2]);
    int align = static_cast<int>(data[3]);
    int componentID = static_cast<int>(data[4]);

    // Call the function under test
    unsigned long result = tjPlaneSizeYUV(componentID, width, height, subsamp, align);

    // Print the result for debugging purposes (optional)
    std::cout << "tjPlaneSizeYUV result: " << result << std::endl;

    return 0;
}