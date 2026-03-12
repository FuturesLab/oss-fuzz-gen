#include <cstdint>
#include <cstdlib>

// Include the correct path for the turbojpeg.h
extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    int width = 1;  // Minimum width
    int height = 1; // Minimum height
    int subsamp = TJSAMP_444; // Assuming 4:4:4 subsampling
    int align = 1;  // Minimum alignment
    int plane = 0;  // Default plane

    // Call the function-under-test
    size_t result = tj3YUVPlaneSize(width, height, subsamp, align, plane);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}