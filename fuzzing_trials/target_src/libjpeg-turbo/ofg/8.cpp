#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Allocate memory for the decompressed YUV image
    // Assuming a reasonable size for the output buffer
    int width = 128;  // Example width
    int height = 128; // Example height
    int yuvSize = tjBufSizeYUV2(width, 4, height, TJ_420);
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompressToYUV(handle, (unsigned char *)data, (unsigned long)size, yuvBuffer, 4);

    // Clean up
    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}