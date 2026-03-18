#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize variables for tjEncodeYUV3
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Failed to initialize TurboJPEG compressor
    }

    const unsigned char *srcBuf = data;
    int width = 100;  // Example width
    int pitch = 0;    // Auto-calculate pitch
    int height = 100; // Example height
    int pixelFormat = TJPF_RGB; // Example pixel format

    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, pitch, height, pixelFormat));
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0; // Memory allocation failed
    }

    int subsamp = TJSAMP_420; // Example subsampling
    int flags = 0;            // No flags
    int align = 1;            // Example alignment value

    // Call the function-under-test with the correct number of arguments
    int result = tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, align, subsamp, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}