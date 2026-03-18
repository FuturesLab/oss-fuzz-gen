#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    const unsigned char *srcBuf = data;
    int width = 64;  // Example width
    int height = 64; // Example height
    int pitch = width * 3; // Assuming 3 bytes per pixel for RGB
    int pixelFormat = TJPF_RGB; // Example pixel format

    // Allocate memory for the destination YUV buffer
    unsigned char *dstBuf = nullptr;
    int dstSize = tjBufSizeYUV2(width, pitch, height, pixelFormat);
    if (dstSize > 0) {
        dstBuf = (unsigned char *)tjAlloc(dstSize);
    }

    // Call the function-under-test
    if (dstBuf != nullptr) {
        int result = tj3EncodeYUVPlanes8(handle, srcBuf, width, pitch, height, pixelFormat, &dstBuf, &dstSize);
        // Optionally check the result for debugging purposes
        (void)result;

        // Free the allocated YUV buffer
        tjFree(dstBuf);
    }

    // Clean up
    tjDestroy(handle);

    return 0;
}