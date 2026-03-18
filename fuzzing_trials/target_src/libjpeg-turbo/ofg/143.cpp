#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to extract necessary parameters
    if (size < 10) {
        return 0;
    }

    // Initialize parameters for tjDecodeYUV
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Extract parameters from the input data
    const unsigned char *srcBuf = data;
    int pad = data[0] % 4; // YUV padding can be 0, 1, 2, or 3
    int subsamp = data[1] % 5; // YUV subsampling can be 0 to 4
    int width = (data[2] << 8) | data[3]; // Extract width from data
    int height = (data[4] << 8) | data[5]; // Extract height from data
    int pixelFormat = data[6] % TJ_NUMPF; // Pixel format
    int flags = data[7] % 2; // Flags (0 or 1)

    // Allocate destination buffer for the decompressed image
    unsigned char *dstBuf = static_cast<unsigned char *>(malloc(width * height * tjPixelSize[pixelFormat]));
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecodeYUV(handle, srcBuf, pad, subsamp, dstBuf, width, 0, height, pixelFormat, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}