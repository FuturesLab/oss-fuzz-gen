#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the test
    if (size < 10) return 0;

    // Initialize decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) return 0;

    // Prepare output buffer
    int width = 100;  // Example width, adjust as needed
    int height = 100; // Example height, adjust as needed
    int pixelFormat = TJPF_RGB; // Example pixel format

    unsigned long jpegSize = size;
    unsigned char *jpegBuffer = (unsigned char *)malloc(size);
    if (jpegBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(jpegBuffer, data, size);

    unsigned char *dstBuffer = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuffer == nullptr) {
        free(jpegBuffer);
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompress(handle, jpegBuffer, jpegSize, dstBuffer, width, 0, height, pixelFormat, TJFLAG_FASTDCT);

    // Clean up
    free(jpegBuffer);
    free(dstBuffer);
    tjDestroy(handle);

    return 0;
}