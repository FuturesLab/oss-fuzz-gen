#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    if (size < 128 * 128 * 3) return 0; // Ensure there's enough data for a 128x128 RGB image

    // Initialize TurboJPEG handle
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Define image dimensions and subsampling
    int width = 128;  // Example width
    int height = 128; // Example height
    int pitch = width * 3; // Assuming 3 bytes per pixel (RGB)
    int subsamp = TJSAMP_444; // Example subsampling

    // Allocate memory for the destination buffer
    unsigned char *dstBuf = nullptr;
    unsigned long dstSize = 0;

    // Call the function-under-test with valid input data
    if (tjCompress2(handle, data, width, pitch, height, TJPF_RGB, &dstBuf, &dstSize, subsamp, 100, 0) == 0) {
        // Successfully compressed the image
    }

    // Clean up
    if (dstBuf) {
        tjFree(dstBuf);
    }
    tjDestroy(handle);

    return 0;
}