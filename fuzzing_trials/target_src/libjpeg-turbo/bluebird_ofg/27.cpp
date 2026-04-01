#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern "C" {
    #include "../src/turbojpeg.h"
    // Removed the non-existent tjtypes.h include
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Define image dimensions and pixel format
    int width = 256; // Example width
    int height = 256; // Example height
    int pitch = width * sizeof(uint16_t); // Calculate pitch using uint16_t for 16-bit samples
    int pixelFormat = TJPF_RGB; // Example pixel format

    // Allocate memory for the compressed image
    unsigned char *compressedImage = NULL;
    size_t compressedSize = 0;

    // Ensure the input data is large enough to represent an image
    if (size < width * height * sizeof(uint16_t)) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tj3Compress16(handle, (const uint16_t *)data, width, pitch, height, pixelFormat, &compressedImage, &compressedSize);

    // Free the compressed image buffer if it was allocated
    if (compressedImage != NULL) {
        tj3Free(compressedImage);
    }

    // Clean up and destroy the TurboJPEG handle
    tj3Destroy(handle);

    return 0;
}