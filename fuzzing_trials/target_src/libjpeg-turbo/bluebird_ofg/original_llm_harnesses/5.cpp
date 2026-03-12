extern "C" {
    #include <stddef.h>
    #include <stdint.h>
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Declare and initialize variables with non-NULL values
    int width = 1; // Minimum valid width
    int height = 1; // Minimum valid height
    int subsamp = TJSAMP_444; // A valid subsampling option from libjpeg-turbo
    int align = 1; // Minimum valid alignment

    // Call the function-under-test
    size_t yuvBufSize = tj3YUVBufSize(width, height, subsamp, align);

    // Use the result to prevent compiler optimizations from removing the function call
    (void)yuvBufSize;

    return 0;
}