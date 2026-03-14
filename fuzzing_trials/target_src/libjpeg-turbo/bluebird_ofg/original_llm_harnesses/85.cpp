#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    unsigned char *jpegBuf = const_cast<unsigned char*>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 1, height = 1, jpegSubsamp = 0, jpegColorspace = 0;

    // Get the JPEG header to determine the width and height
    if (tjDecompressHeader3(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, jpegSubsamp));
    if (yuvBuf == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompressToYUV(handle, jpegBuf, jpegSize, yuvBuf, 4);

    // Clean up
    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}