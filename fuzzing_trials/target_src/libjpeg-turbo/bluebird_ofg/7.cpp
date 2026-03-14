#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm> // For std::min

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Initialize the necessary variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    const char *filename = "output_image.tiff"; // Example filename

    // Create a small buffer for uint16_t (assuming J16SAMPLE is uint16_t)
    int width = 2;  // Example width
    int height = 2; // Example height
    int numComponents = 3; // Example number of components (e.g., RGB)
    int pixelFormat = TJPF_RGB; // Example pixel format
    size_t bufferSize = width * height * numComponents * sizeof(uint16_t);
    uint16_t *sampleBuffer = (uint16_t *)malloc(bufferSize);

    if (sampleBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Fill the sample buffer with data
    memcpy(sampleBuffer, data, std::min(size, bufferSize));

    // Call the function-under-test
    int result = tj3SaveImage16(handle, filename, sampleBuffer, width, 0, height, pixelFormat);

    // Clean up
    free(sampleBuffer);
    tjDestroy(handle);

    return 0;
}