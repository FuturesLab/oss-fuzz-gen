extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    tjhandle handle = nullptr;
    unsigned char *yuvBuffer = nullptr;
    int width = 0, height = 0, jpegSubsamp = 0, jpegColorspace = 0;
    int flags = 0;  // No specific flags for now

    if (size < 10) { // Ensure there's enough data to be a valid JPEG
        return 0;
    }

    // Initialize TurboJPEG decompressor
    handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Get JPEG header info
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate buffer for YUV image
    yuvBuffer = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, jpegSubsamp));
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompressToYUV(handle, const_cast<unsigned char *>(data), size, yuvBuffer, flags);

    // Clean up
    free(yuvBuffer);
    tjDestroy(handle);

    return 0;
}