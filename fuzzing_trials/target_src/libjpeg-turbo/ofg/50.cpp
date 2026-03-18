#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Define dimensions and subsampling for the output YUV image
    int width = 640;
    int height = 480;
    int subsamp = TJSAMP_420; // Common subsampling format
    int flags = 0;

    // Calculate the buffer size for the YUV image
    int align = 4; // Alignment parameter for tjBufSizeYUV2
    unsigned long yuvSize = tjBufSizeYUV2(width, align, height, subsamp);

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0; // If allocation fails, exit early
    }

    // Call the function-under-test
    int result = tjDecompressToYUV2(handle, data, size, yuvBuffer, width, align, height, flags);

    // Clean up resources
    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}