#include <cstdint>
#include <cstdlib>
#include <cstring> // For memcpy

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Ensure there's enough data for the parameters
    if (size < 8) {
        tjDestroy(handle);
        return 0;
    }

    // Extract parameters from the input data
    int width = data[0] + 1;  // Avoid zero width
    int height = data[1] + 1; // Avoid zero height
    int strides[3] = {width, width / 2, width / 2}; // YUV strides

    // Allocate memory for YUV and RGB buffers
    unsigned char *yuvBuffer = (unsigned char *)malloc(width * height * 3 / 2);
    unsigned char *rgbBuffer = (unsigned char *)malloc(width * height * 3);

    if (yuvBuffer == nullptr || rgbBuffer == nullptr) {
        free(yuvBuffer);
        free(rgbBuffer);
        tjDestroy(handle);
        return 0;
    }

    // Copy input data to yuvBuffer
    size_t copySize = size < (width * height * 3 / 2) ? size : (width * height * 3 / 2);
    memcpy(yuvBuffer, data, copySize);

    // Call the function-under-test
    tj3DecodeYUV8(handle, yuvBuffer, strides[0], rgbBuffer, width, 0, height, 0);

    // Clean up
    free(yuvBuffer);
    free(rgbBuffer);
    tjDestroy(handle);

    return 0;
}