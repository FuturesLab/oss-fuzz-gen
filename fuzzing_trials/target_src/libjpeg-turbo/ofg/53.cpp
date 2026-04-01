#include <stddef.h>
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Define YUV planes
    const unsigned char *yuvPlanes[3];
    int width = 16; // Example width
    int height = 8; // Example height
    int strides[3] = {width, width / 2, width / 2}; // Strides for Y, U, and V planes
    size_t compressedSize = 0;
    unsigned char *compressedBuffer = nullptr;

    // Ensure the size is sufficient for the YUV data
    if (size < width * height * 3 / 2) {
        tj3Destroy(handle);
        return 0;
    }

    // Assign data to YUV planes
    yuvPlanes[0] = data; // Y plane
    yuvPlanes[1] = data + width * height; // U plane
    yuvPlanes[2] = data + width * height * 5 / 4; // V plane

    // Allocate memory for compressed buffer
    size_t bufSize = tjBufSize(width, height, TJSAMP_420);
    compressedBuffer = (unsigned char*)malloc(bufSize);
    if (compressedBuffer == nullptr) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    if (tj3CompressFromYUVPlanes8(handle, yuvPlanes, width, strides, height, &compressedBuffer, &compressedSize) == -1) {
        // Handle error
        tj3Destroy(handle);
        free(compressedBuffer);
        return 0;
    }

    // Simulate some usage of compressed data to ensure code coverage
    if (compressedSize > 0) {
        // For example, we can just read the first byte
        volatile unsigned char firstByte = compressedBuffer[0];
        (void)firstByte; // Avoid unused variable warning
    }

    // Clean up
    tj3Destroy(handle);
    free(compressedBuffer);

    return 0;
}