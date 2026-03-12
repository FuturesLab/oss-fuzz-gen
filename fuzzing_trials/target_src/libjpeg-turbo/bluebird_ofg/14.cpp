#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    if (size < 10) return 0; // Ensure there's enough data for basic operation

    // Initialize the TurboJPEG compressor
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) return 0;

    // Prepare input parameters
    unsigned char *srcBuf = (unsigned char *)malloc(size);
    if (srcBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(srcBuf, data, size);

    int width = 100; // Example width
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format
    int quality = 75; // Example quality
    int flags = 0; // Example flags

    // Prepare output parameters
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSize(width, height, TJSAMP_444));
    if (dstBuf == nullptr) {
        free(srcBuf);
        tjDestroy(handle);
        return 0;
    }
    unsigned long dstSize = tjBufSize(width, height, TJSAMP_444);

    // Call the function-under-test
    int result = tjCompress(handle, srcBuf, width, 0, height, pixelFormat, dstBuf, &dstSize, TJSAMP_444, quality, flags);

    // Clean up
    free(dstBuf);
    free(srcBuf);
    tjDestroy(handle);

    return 0;
}