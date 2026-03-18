#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"

    int tjSaveImage(const char *, unsigned char *, int, int, int, int, int);
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Define and initialize variables for the function parameters
    const char *filename = "test.jpg";  // Dummy filename for saving the image
    unsigned char *imageBuffer = nullptr;
    int width = 100;   // Example width
    int height = 100;  // Example height
    int pitch = 0;     // Example pitch
    int pixelFormat = TJPF_RGB;  // Example pixel format
    int flags = 0;     // Example flags

    // Allocate memory for the image buffer
    size_t bufferSize = width * height * tjPixelSize[pixelFormat];
    if (size < bufferSize) {
        return 0;  // Not enough data to fill the image buffer
    }
    imageBuffer = (unsigned char *)malloc(bufferSize);
    if (imageBuffer == nullptr) {
        return 0;  // Memory allocation failed
    }

    // Copy data into the image buffer
    memcpy(imageBuffer, data, bufferSize);

    // Call the function-under-test
    tjSaveImage(filename, imageBuffer, width, pitch, height, pixelFormat, flags);

    // Free allocated memory
    free(imageBuffer);

    return 0;
}