#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Not enough data to proceed
    }

    // Initialize TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Initialization failed, exit early
    }

    // Allocate buffers for decompression
    unsigned char *jpegBuf = (unsigned char *)malloc(size);
    if (jpegBuf == nullptr) {
        tjDestroy(handle);
        return 0; // Memory allocation failed
    }
    memcpy(jpegBuf, data, size);

    int width = 100;  // Dummy width
    int height = 100; // Dummy height
    int jpegSubsamp = TJSAMP_444; // Dummy subsampling
    int jpegColorspace = TJCS_RGB; // Dummy colorspace

    // Decompress the image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
    if (dstBuf == nullptr) {
        free(jpegBuf);
        tjDestroy(handle);
        return 0; // Memory allocation failed
    }

    // Call the function-under-test
    int result = tjDecompress(handle, jpegBuf, size, dstBuf, width, 0 /* pitch */, height, TJPF_RGB, 0);

    // Clean up
    free(jpegBuf);
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}