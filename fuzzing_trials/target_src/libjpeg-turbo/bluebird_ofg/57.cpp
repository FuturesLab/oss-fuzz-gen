#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Initialize parameters for tj3EncodeYUV8
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Failed to initialize handle
    }

    // Ensure the input size is sufficient for the parameters
    if (size < 4) {
        tj3Destroy(handle);
        return 0;
    }

    // Define and initialize parameters for tj3EncodeYUV8
    const unsigned char *srcBuf = data;
    int width = 2;  // Minimum width for a valid image
    int height = 2; // Minimum height for a valid image
    int pitch = 0;  // Auto-calculate pitch
    int subsamp = TJSAMP_444; // Use 4:4:4 subsampling
    int align = 1; // Default alignment
    unsigned char *dstBuf = (unsigned char *)malloc(tj3YUVBufSize(width, align, height, subsamp));
    int flags = 0; // No flags

    // Call the function-under-test
    tj3EncodeYUV8(handle, srcBuf, width, pitch, height, subsamp, dstBuf, flags);

    // Clean up
    free(dstBuf);
    tj3Destroy(handle);

    return 0;
}