#include <stddef.h>
#include <stdint.h>
#include <stdio.h> // Include this for FILE type

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/jpeglib.h"
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == nullptr) {
        return 0;
    }

    // Define width and height for the decompressed image
    int width = 100;  // Example width
    int height = 100; // Example height

    // Calculate the size of the decompressed image buffer
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = width * tjPixelSize[pixelFormat];
    size_t decompressedSize = pitch * height;

    // Allocate buffer for the decompressed image
    J16SAMPLE *decompressedBuffer = new J16SAMPLE[decompressedSize];
    if (decompressedBuffer == nullptr) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tj3Decompress16(handle, data, size, decompressedBuffer, width, height);

    // Clean up
    delete[] decompressedBuffer;
    tj3Destroy(handle);

    return 0;
}