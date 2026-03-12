#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0;
    }

    // Initialize parameters for tjDecodeYUV
    tjhandle handle = tjInitDecompress();
    const unsigned char *srcBuf = data;
    int width = 128;  // Example width, can vary
    int pad = 4;      // Example padding, can vary
    int height = 128; // Example height, can vary
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3); // Allocate buffer for RGB image
    int pitch = 0;    // Default pitch
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0;    // Default flags
    int subsamp = TJSAMP_420; // Example subsampling

    if (handle == nullptr || dstBuf == nullptr) {
        if (handle != nullptr) {
            tjDestroy(handle);
        }
        if (dstBuf != nullptr) {
            free(dstBuf);
        }
        return 0;
    }

    // Call the function-under-test
    int result = tjDecodeYUV(handle, srcBuf, pad, width, dstBuf, pitch, height, pixelFormat, subsamp, flags);

    // Clean up
    tjDestroy(handle);
    free(dstBuf);

    return 0;
}