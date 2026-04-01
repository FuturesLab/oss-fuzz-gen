#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    // Define some parameters for the decompression
    int width = 100;  // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // No flags
    int pitch = width * tjPixelSize[pixelFormat]; // Calculate pitch

    // Allocate buffer for decompressed image
    unsigned char* destBuf = (unsigned char*)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!destBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecompress2(handle, data, (unsigned long)size, destBuf, width, pitch, height, pixelFormat, flags);

    // Clean up
    free(destBuf);
    tjDestroy(handle);

    return 0;
}