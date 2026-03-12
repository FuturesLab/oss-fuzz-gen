#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Declare and initialize the variables needed for tjEncodeYUV2
    tjhandle handle = nullptr;
    unsigned char *srcBuf = nullptr;
    unsigned char *dstBuf = nullptr;
    int width = 1;  // Minimum width
    int height = 1; // Minimum height
    int pitch = 0;  // Auto-calculate pitch
    int subsamp = TJSAMP_444; // Default subsampling
    int align = 1;  // Default alignment
    int flags = 0;  // Default flags

    // Initialize the TurboJPEG compressor
    handle = tjInitCompress();
    if (handle == nullptr) return 0;

    // Ensure data is not empty and allocate srcBuf
    if (size > 0) {
        srcBuf = (unsigned char *)malloc(size);
        if (srcBuf == nullptr) {
            tjDestroy(handle);
            return 0;
        }
        memcpy(srcBuf, data, size);

        // Allocate dstBuf for YUV output
        int yuvSize = tjBufSizeYUV2(width, align, height, subsamp);
        dstBuf = (unsigned char *)malloc(yuvSize);
        if (dstBuf == nullptr) {
            free(srcBuf);
            tjDestroy(handle);
            return 0;
        }

        // Call the function under test
        tjEncodeYUV2(handle, srcBuf, width, pitch, height, subsamp, dstBuf, align, flags);
    }

    // Cleanup
    if (srcBuf != nullptr) free(srcBuf);
    if (dstBuf != nullptr) free(dstBuf);
    if (handle != nullptr) tjDestroy(handle);

    return 0;
}