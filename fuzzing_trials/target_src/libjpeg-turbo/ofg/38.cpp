extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Initialize the parameters for tjEncodeYUV
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Ensure that the input size is sufficient for at least a small image
    if (size < 3) {
        tjDestroy(handle);
        return 0;
    }

    // Use the input data to determine image dimensions
    int width = data[0] % 256 + 1; // Width should be at least 1
    int height = data[1] % 256 + 1; // Height should be at least 1
    int pixelFormat = TJPF_RGB; // Assume input is RGB format
    int padding = 1; // TJ_PAD(1) for no padding
    int subsampling = TJSAMP_444; // Use a common subsampling format

    // Allocate memory for the source image and the destination YUV image
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, padding, height, subsampling));

    if (srcBuf == nullptr || dstBuf == nullptr) {
        free(srcBuf);
        free(dstBuf);
        tjDestroy(handle);
        return 0;
    }

    // Fill the source buffer with input data
    size_t copySize = width * height * tjPixelSize[pixelFormat];
    if (copySize > size - 2) {
        copySize = size - 2;
    }
    memcpy(srcBuf, data + 2, copySize);

    // Call the function-under-test
    tjEncodeYUV(handle, srcBuf, width, padding, height, pixelFormat, dstBuf, subsampling, 0);

    // Clean up
    free(srcBuf);
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}