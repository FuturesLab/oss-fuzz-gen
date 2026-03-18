#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == NULL) {
        return 0;
    }

    // Ensure there's enough data to proceed
    if (size < sizeof(uint16_t)) { // Use uint16_t instead of J16SAMPLE
        tjDestroy(handle);
        return 0;
    }

    // Allocate and initialize input buffer
    uint16_t *inputBuffer = (uint16_t *)malloc(size); // Use uint16_t instead of J16SAMPLE
    if (inputBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(inputBuffer, data, size);

    // Set image dimensions and parameters
    int width = 128;  // Example width
    int height = 128; // Example height
    int pitch = width * sizeof(uint16_t); // Use uint16_t instead of J16SAMPLE
    int pixelFormat = TJPF_RGB; // Example pixel format

    // Allocate output buffer
    unsigned char *jpegBuf = NULL;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3Compress16(handle, inputBuffer, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Clean up
    free(inputBuffer);
    tjFree(jpegBuf);
    tjDestroy(handle);

    return result;
}