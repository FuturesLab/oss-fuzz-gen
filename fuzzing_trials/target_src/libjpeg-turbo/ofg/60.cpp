#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    int width = 1; // Minimum valid value for width
    int height = 1; // Minimum valid value for height
    int subsamp = TJSAMP_444; // Use a valid subsampling option
    int align = 1; // Minimum valid value for alignment

    // Call the function-under-test
    size_t result = tj3YUVPlaneSize(width, height, subsamp, align, 0);

    // Use the result to avoid compiler optimizations
    (void)result;

    return 0;
}