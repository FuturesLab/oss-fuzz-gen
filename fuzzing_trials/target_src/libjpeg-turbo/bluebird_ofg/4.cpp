#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there's at least some data to process

    // Initialize TurboJPEG decompressor
    tjhandle decompressor = tjInitDecompress();
    if (decompressor == nullptr) {
        return 0; // If initialization fails, return
    }

    // Define some parameters for decompression
    int width = 100;  // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = 0; // Auto-calculate the pitch
    int flags = 0; // No flags

    // Allocate memory for the decompressed image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuf == nullptr) {
        tjDestroy(decompressor);
        return 0; // If memory allocation fails, return
    }

    // Call the function-under-test
    int result = tjDecompress2(decompressor, data, (unsigned long)size, dstBuf, width, pitch, height, pixelFormat, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(decompressor);

    return 0;
}