#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    const char *filename = "output.jpg"; // Use a fixed filename for testing
    int width = 10; // Arbitrary non-zero width
    int height = 10; // Arbitrary non-zero height
    int pitch = width * sizeof(uint16_t); // Pitch (bytes per row)
    int flags = 0; // No specific flags for now

    // Ensure we have enough data to fill the image buffer
    if (size < width * height * sizeof(uint16_t)) {
        return 0;
    }

    // Allocate and initialize the image buffer
    uint16_t *imageBuffer = (uint16_t *)malloc(width * height * sizeof(uint16_t));
    if (imageBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Copy the data into the image buffer
    memcpy(imageBuffer, data, width * height * sizeof(uint16_t));

    // Call the function-under-test
    int result = tj3SaveImage16(handle, filename, imageBuffer, width, pitch, height, flags);

    // Clean up
    free(imageBuffer);
    tjDestroy(handle);

    return 0;
}