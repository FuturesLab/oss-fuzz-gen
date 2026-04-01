#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize TurboJPEG compressor
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Failed to initialize compressor
    }

    // Extract dimensions and pixel format from the input data
    int width = data[0] + 1;  // Ensure width is at least 1
    int height = data[1] + 1; // Ensure height is at least 1
    int pixelFormat = data[2] % TJ_NUMPF; // Choose a valid pixel format

    // Set JPEG quality and subsampling
    int jpegQuality = data[3] % 101; // Quality between 0 and 100
    int subsample = data[4] % TJ_NUMSAMP; // Choose a valid subsampling option

    // Calculate the minimum buffer size needed for the input image
    int bytesPerPixel = tjPixelSize[pixelFormat];
    size_t minBufferSize = width * height * bytesPerPixel;

    // Ensure we have enough data for the image buffer
    if (size < 5 + minBufferSize) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjDestroy with tjGetErrorCode
        tjGetErrorCode(handle);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0;
    }

    // Allocate memory for the compressed image
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Call the function-under-test
    int result = tjCompress2(
        handle, 
        data + 5, // Offset data to allow room for width, height, etc.
        width, 
        0, // pitch (0 means use width * bytesPerPixel)
        height, 
        pixelFormat, 
        &jpegBuf, 
        &jpegSize, 
        subsample, 
        jpegQuality, 
        TJFLAG_FASTDCT // Use fast DCT for compression
    );

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}