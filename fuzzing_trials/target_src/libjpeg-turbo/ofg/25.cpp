#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h" // Ensure the correct header is included
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    if (size < sizeof(uint16_t)) { // Assuming J16SAMPLE is a 16-bit sample, use uint16_t
        return 0; // Not enough data to form a valid sample
    }

    // Initialize parameters for tj3Compress16
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        return 0; // Failed to initialize
    }

    // Allocate memory for input
    uint16_t *j16Sample = (uint16_t *)malloc(size);
    if (!j16Sample) {
        tj3Destroy(handle);
        return 0; // Memory allocation failed
    }
    memcpy(j16Sample, data, size);

    int width = 1; // Minimum valid width
    int height = 1; // Minimum valid height
    int pitch = width * sizeof(uint16_t); // Assuming pitch is width * sizeof(uint16_t)
    int pixelFormat = TJPF_RGB; // Assuming RGB format

    unsigned char *compressedImage = nullptr;
    size_t compressedSize = 0;

    // Call the function under test
    int result = tj3Compress16(handle, j16Sample, width, pitch, height, pixelFormat, &compressedImage, &compressedSize);

    // Clean up
    if (compressedImage) {
        tj3Free(compressedImage);
    }
    free(j16Sample);
    tj3Destroy(handle);

    return 0;
}