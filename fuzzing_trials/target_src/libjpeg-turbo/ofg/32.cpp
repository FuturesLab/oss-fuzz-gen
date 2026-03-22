#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Create a buffer for the decompressed image
    int width = 256; // Example width
    int height = 256; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = width * tjPixelSize[pixelFormat];
    unsigned char *destBuffer = (unsigned char *)malloc(pitch * height);

    if (destBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompress2(handle, data, size, destBuffer, width, pitch, height, pixelFormat, 0);

    // Clean up
    free(destBuffer);
    tjDestroy(handle);

    return 0;
}