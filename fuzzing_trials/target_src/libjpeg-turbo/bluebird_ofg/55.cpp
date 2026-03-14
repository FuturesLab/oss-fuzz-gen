#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0;
    }

    // Ensure the size is large enough to contain necessary data
    if (size < 10) {
        tj3Destroy(handle);
        return 0;
    }

    // Define and initialize parameters
    const unsigned char *srcBuf = data;
    int pad = 4; // Typical padding value for YUV formats
    int width = 2; // Minimal width for testing
    int height = 2; // Minimal height for testing
    int flags = 0; // No specific flags for now

    // Allocate destination buffer for the decoded image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3); // Assuming RGB output

    if (!dstBuf) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    tj3DecodeYUV8(handle, srcBuf, pad, dstBuf, width, width, height, flags);

    // Clean up
    free(dstBuf);
    tj3Destroy(handle);

    return 0;
}