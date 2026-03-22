#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    tjhandle handle = NULL;
    unsigned char *outputBuffer = NULL; // Changed from J16SAMPLE to unsigned char
    int width = 64;  // Example width, can be varied
    int height = 64; // Example height, can be varied
    int pixelFormat = TJPF_RGB; // Example pixel format
    int result;

    // Initialize TurboJPEG decompressor
    handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the output buffer
    outputBuffer = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (outputBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    result = tjDecompress2(handle, data, size, outputBuffer, width, 0 /* pitch */, height, pixelFormat, TJFLAG_FASTDCT);

    // Clean up
    free(outputBuffer);
    tjDestroy(handle);

    return 0;
}