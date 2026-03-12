#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for the parameters
    if (size < 100) return 0; // Adjust this based on realistic minimum size needed

    // Initialize parameters for tjEncodeYUV2
    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    unsigned char *srcBuf = const_cast<unsigned char*>(data);
    int width = 10;  // Example width, adjust as needed
    int pitch = 0;   // Use 0 to indicate the pitch should be calculated
    int height = 10; // Example height, adjust as needed
    int pixelFormat = TJPF_RGB; // Example pixel format, adjust as needed

    // Allocate destination buffer
    unsigned long yuvSize = tjBufSizeYUV2(width, pitch, height, TJSAMP_444);
    unsigned char *dstBuf = (unsigned char *)malloc(yuvSize);
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    int subsamp = TJSAMP_444; // Example subsampling, adjust as needed
    int flags = 0; // No flags for now

    // Call the function-under-test
    int result = tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, subsamp, flags);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}