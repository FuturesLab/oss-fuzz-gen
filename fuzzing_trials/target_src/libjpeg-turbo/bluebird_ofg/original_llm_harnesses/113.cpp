#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    int width = 100;  // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format

    // Allocate buffer for decompressed image
    unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!buffer) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompress2(handle, data, size, buffer, width, 0 /* pitch */, height, pixelFormat, TJFLAG_FASTDCT);

    // Clean up
    free(buffer);
    tjDestroy(handle);

    return 0;
}