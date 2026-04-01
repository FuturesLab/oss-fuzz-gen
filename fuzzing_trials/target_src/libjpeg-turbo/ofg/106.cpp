#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the input data is large enough to set dimensions and pixel format
    if (size < 6) { // At least 6 bytes to set width, height, and pixel format
        tj3Destroy(handle);
        return 0;
    }

    // Set image dimensions and pixel format from input data
    int width = data[0] + (data[1] << 8);  // Use first two bytes for width
    int height = data[2] + (data[3] << 8); // Use next two bytes for height
    int pixelFormat = data[4] % TJ_NUMPF;  // Use fifth byte for pixel format, ensure it's valid
    int pitch = width * tjPixelSize[pixelFormat];

    // Ensure the input data is large enough to represent an image
    if (size < 6 + width * height * tjPixelSize[pixelFormat]) {
        tj3Destroy(handle);
        return 0;
    }

    // Allocate memory for the output buffer
    unsigned char *compressedBuffer = nullptr;
    size_t compressedSize = 0;

    // Call the function-under-test
    int result = tj3Compress8(handle, data + 6, width, pitch, height, pixelFormat, &compressedBuffer, &compressedSize);

    // Free the allocated compressed buffer if it was allocated
    if (compressedBuffer != nullptr) {
        tj3Free(compressedBuffer);
    }

    // Clean up the TurboJPEG handle
    tj3Destroy(handle);

    return 0;
}