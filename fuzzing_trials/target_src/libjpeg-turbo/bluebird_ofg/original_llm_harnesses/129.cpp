#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    // Prepare parameters for tj3SaveImage16
    const char *filename = "output.tiff"; // Sample output filename

    // Allocate memory for uint16_t array (assuming J16SAMPLE is uint16_t)
    int width = 2; // Example width
    int height = 2; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = width * tjPixelSize[pixelFormat];

    uint16_t *imageBuffer = (uint16_t *)malloc(sizeof(uint16_t) * width * height * tjPixelSize[pixelFormat]);
    if (imageBuffer == nullptr) {
        tj3Destroy(handle);
        return 0; // Memory allocation failed
    }

    // Fill the imageBuffer with data
    memcpy(imageBuffer, data, std::min(size, sizeof(uint16_t) * width * height * tjPixelSize[pixelFormat]));

    // Call the function-under-test
    int result = tj3SaveImage16(handle, filename, imageBuffer, width, pitch, height, pixelFormat);

    // Clean up
    free(imageBuffer);
    tj3Destroy(handle);

    return 0;
}