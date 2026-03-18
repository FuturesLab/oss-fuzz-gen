#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Initialize variables for tjDecompress
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    unsigned char *jpegBuf = const_cast<unsigned char *>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);

    // Set up output buffer
    int width = 100;  // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = width * tjPixelSize[pixelFormat];
    unsigned char *dstBuf = static_cast<unsigned char *>(malloc(pitch * height));

    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0; // If memory allocation fails, exit early
    }

    // Call the function-under-test
    int result = tjDecompress(handle, jpegBuf, jpegSize, dstBuf, width, pitch, height, pixelFormat, 0);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}