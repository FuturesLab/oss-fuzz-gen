#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0; // If initialization fails, return early
    }

    unsigned char *jpegBuf = const_cast<unsigned char *>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);

    // Allocate a buffer for the YUV image
    int width = 1;  // Minimal non-zero width
    int height = 1; // Minimal non-zero height
    int subsamp = TJSAMP_444; // Use a common subsampling factor
    int yuvSize = tjBufSizeYUV2(width, 1, height, subsamp);
    unsigned char *yuvBuf = new unsigned char[yuvSize];

    // Call the function-under-test
    tjDecompressToYUV(handle, jpegBuf, jpegSize, yuvBuf, 1);

    // Clean up
    delete[] yuvBuf;
    tjDestroy(handle);

    return 0;
}