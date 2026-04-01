#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Wrap the inclusion of the C library with extern "C"
extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Initialize TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Failed to initialize
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0; // Failed to read header
    }

    // Allocate memory for the output image
    int pixelFormat = TJPF_RGB; // Output pixel format
    unsigned char *outputBuffer = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);

    if (outputBuffer == NULL) {
        tjDestroy(handle);
        return 0; // Failed to allocate output buffer
    }

    // Call the function-under-test
    if (tjDecompress2(handle, data, size, outputBuffer, width, 0, height, pixelFormat, 0) != 0) {
        free(outputBuffer);
        tjDestroy(handle);
        return 0; // Decompression failed
    }

    // Clean up
    free(outputBuffer);
    tjDestroy(handle);

    return 0;
}