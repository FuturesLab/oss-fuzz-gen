#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there is enough data for the parameters
    }

    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit
    }

    // Extract parameters from the input data
    int width = static_cast<int>(data[0]) + 1;  // Width must be at least 1
    int height = static_cast<int>(data[1]) + 1; // Height must be at least 1
    int stride = static_cast<int>(data[2]) + 1; // Stride must be at least 1
    int subsamp = data[3] % 5; // Subsampling value (0-4)
    int flags = data[4] % 2;   // Flags (0 or 1)

    // Calculate the size of the YUV buffer
    int yuvSize = tjBufSizeYUV2(width, stride, height, subsamp);
    if (yuvSize < 0 || static_cast<size_t>(yuvSize) > size - 5) {
        tjDestroy(handle);
        return 0; // If the buffer size is invalid or too large, exit
    }

    // Allocate memory for the destination image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0; // If memory allocation fails, exit
    }

    // Call the function-under-test
    int result = tjDecodeYUV(handle, data + 5, stride, subsamp, dstBuf, width, 0, height, TJPF_RGB, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}