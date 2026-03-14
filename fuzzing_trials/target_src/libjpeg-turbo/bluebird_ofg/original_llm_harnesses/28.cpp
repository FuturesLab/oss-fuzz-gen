#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for memcpy and memset

// Include the correct path for turbojpeg.h and wrap it with extern "C"
extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Define and initialize parameters for tjSaveImage
    const char *filename = "output.jpg"; // File name to save the image
    unsigned char *imageBuffer = nullptr;
    int width = 100; // Example width
    int height = 100; // Example height
    int pitch = 0; // Pitch can be 0 for tightly packed pixels
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // No specific flags

    // Allocate memory for the image buffer
    imageBuffer = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (imageBuffer == nullptr) {
        return 0; // Memory allocation failed, exit early
    }

    // Copy data to image buffer if size is sufficient
    if (size >= width * height * tjPixelSize[pixelFormat]) {
        memcpy(imageBuffer, data, width * height * tjPixelSize[pixelFormat]);
    } else {
        // If the provided data size is smaller, fill with a pattern or zeros
        memset(imageBuffer, 0, width * height * tjPixelSize[pixelFormat]);
    }

    // Call the function-under-test
    tjSaveImage(filename, imageBuffer, width, pitch, height, pixelFormat, flags);

    // Free the allocated memory
    free(imageBuffer);

    return 0;
}