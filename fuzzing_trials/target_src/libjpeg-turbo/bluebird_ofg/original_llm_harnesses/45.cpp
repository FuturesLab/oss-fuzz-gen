#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 1, height = 1, jpegSubsamp = TJSAMP_444, jpegColorspace = TJCS_RGB;
    int pixelFormat = TJPF_RGB;

    // Decompress the JPEG header to get the image dimensions
    if (tjDecompressHeader3(handle, data, jpegSize, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate buffer for the decompressed image
    unsigned char *dstBuf = static_cast<unsigned char *>(malloc(width * height * tjPixelSize[pixelFormat]));
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjDecompress2(handle, data, jpegSize, dstBuf, width, 0 /* pitch */, height, pixelFormat, 0);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}