#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Declare and initialize parameters for tjBufSizeYUV2
    int width = 1;  // Minimum width to ensure non-zero buffer size
    int height = 1; // Minimum height to ensure non-zero buffer size
    int subsamp = TJSAMP_420; // Common subsampling option
    int align = 1;  // Minimum alignment

    // Call the function-under-test
    unsigned long bufferSize = tjBufSizeYUV2(width, height, subsamp, align);

    // Use the result in some way to avoid compiler optimizations removing the call
    // For fuzzing purposes, we just ensure the function is called
    (void)bufferSize;

    return 0;
}