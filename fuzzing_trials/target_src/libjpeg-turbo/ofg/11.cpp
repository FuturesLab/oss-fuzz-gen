#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < 10) { // Ensure there's enough data for width, height, and pixel format
        return 0;
    }

    // Initialize TurboJPEG handle
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Extract width, height, and pixel format from the input data
    int width = data[0] + 1; // Ensure non-zero width
    int height = data[1] + 1; // Ensure non-zero height
    int pixelFormat = data[2] % TJ_NUMPF; // Use a valid pixel format

    // Allocate memory for the compressed image
    unsigned char *compressedImage = nullptr;
    unsigned long compressedSize = 0;

    // Set the rest of the input data as the image buffer
    const unsigned char *imageBuffer = data + 3;
    int pitch = width * tjPixelSize[pixelFormat];

    // Call the function-under-test
    int result = tjCompress2(
        handle, 
        imageBuffer, 
        width, 
        pitch, 
        height, 
        pixelFormat, 
        &compressedImage, 
        &compressedSize, 
        TJSAMP_444, // Use a valid subsampling option
        75, // Set quality to a typical value
        TJFLAG_FASTDCT // Use a valid flag
    );

    // Clean up
    if (compressedImage != nullptr) {
        tjFree(compressedImage);
    }
    tjDestroy(handle);

    return 0;
}