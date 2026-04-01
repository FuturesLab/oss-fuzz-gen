#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Include the correct path for turbojpeg.h
extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to process
    }

    // Extract parameters from the input data
    int width = data[0] + 1;  // Ensure width is at least 1
    int height = data[1] + 1; // Ensure height is at least 1
    int subsamp = data[2] % TJSAMP_GRAY; // Use a valid subsampling option
    int plane = 0; // Start with the first plane
    int align = 1; // Minimum valid alignment

    // Call the function-under-test with the initialized parameters
    unsigned long result = tjPlaneSizeYUV(width, height, subsamp, plane, align);

    // Use the result (here we just suppress the unused variable warning)
    (void)result;

    return 0;
}