#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    if (size < 20) { // Ensure there's enough data for meaningful testing
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0;
    }

    // Extract width and height from the input data
    int width = data[0] % 256 + 1; // Ensure width is at least 1
    int height = data[1] % 256 + 1; // Ensure height is at least 1
    int subsamp = TJSAMP_420; // Common subsampling
    int flags = 0; // No flags

    // Calculate the required buffer size for the YUV image
    int yuvSize = tjBufSizeYUV2(width, 1, height, subsamp);
    if (yuvSize > size - 2) { // Adjust for width and height bytes
        tjDestroy(handle);
        return 0; // Not enough data to fill the YUV buffer
    }

    // Assign the data to YUV planes
    const unsigned char *yuvPlanes[3];
    yuvPlanes[0] = data + 2; // Start after width and height bytes
    yuvPlanes[1] = yuvPlanes[0] + (yuvSize / 3);
    yuvPlanes[2] = yuvPlanes[1] + (yuvSize / 3);

    // Set strides for each plane
    int strides[3];
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Allocate destination buffer for the decoded image
    int pixelFormat = TJPF_RGB;
    int dstSize = width * height * tjPixelSize[pixelFormat];
    unsigned char *dstBuffer = (unsigned char *)malloc(dstSize);
    if (!dstBuffer) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecodeYUVPlanes(handle, yuvPlanes, strides, subsamp, dstBuffer, width, 0, height, pixelFormat, flags);

    // Clean up
    free(dstBuffer);
    tjDestroy(handle);

    return 0;
}