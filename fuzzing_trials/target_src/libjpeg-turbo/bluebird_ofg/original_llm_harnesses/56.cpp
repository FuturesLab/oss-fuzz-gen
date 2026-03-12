#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0;
    }

    const unsigned char *srcBuf = data;
    int width = 128;  // Example width
    int height = 128; // Example height
    int pitch = width; // Example pitch, assuming 1 byte per pixel
    int subsamp = TJSAMP_420; // Example subsampling
    unsigned char *dstBuf = nullptr;
    int dstSizes[3] = {0, 0, 0};

    // Allocate memory for destination buffer
    int bufSize = tjBufSizeYUV2(width, pitch, height, subsamp);
    dstBuf = (unsigned char *)malloc(bufSize);
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function under test
    int result = tj3EncodeYUVPlanes8(handle, srcBuf, width, pitch, height, subsamp, &dstBuf, dstSizes);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}