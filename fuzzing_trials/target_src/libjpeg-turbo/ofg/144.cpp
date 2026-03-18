#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for extracting parameters
    if (size < 5) {
        return 0;
    }

    // Extract parameters from the input data
    int width = static_cast<int>(data[0]) + 1;  // Avoid zero width
    int height = static_cast<int>(data[1]) + 1; // Avoid zero height
    int subsamp = static_cast<int>(data[2]) % 6; // Valid subsampling values are 0 to 5
    int align = (static_cast<int>(data[3]) % 16) + 1; // Alignment values are typically powers of 2
    int componentID = static_cast<int>(data[4]) % 3; // Valid component IDs are 0, 1, or 2

    // Call the function-under-test
    unsigned long sizeYUV = tjPlaneSizeYUV(componentID, width, align, height, subsamp);

    // Use the result in some way to prevent compiler optimizations from removing the call
    volatile unsigned long result = sizeYUV;
    (void)result;

    return 0;
}