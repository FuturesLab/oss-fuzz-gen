#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there is enough data for the parameters
    }

    // Initialize tjhandle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Extract parameters from data
    int width = data[0] + 1; // Ensure width is at least 1
    int height = data[1] + 1; // Ensure height is at least 1
    int stride = data[2] + 1; // Ensure stride is at least 1
    int subsamp = data[3] % 5; // Valid subsampling values are 0-4
    int flags = data[4] % 2; // Flags can be 0 or 1

    // Calculate the minimum required size for the YUV buffer
    int yuvSize = tjBufSizeYUV2(width, stride, height, subsamp);
    if (size < 5 + yuvSize) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for the destination buffer
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecodeYUV(handle, data + 5, stride, subsamp, dstBuf, width, 0, height, TJPF_RGB, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}