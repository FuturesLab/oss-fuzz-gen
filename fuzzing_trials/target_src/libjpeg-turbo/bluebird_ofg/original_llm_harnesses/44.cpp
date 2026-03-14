#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    const unsigned char *jpegBuf = data;
    size_t jpegSize = size;

    int width = 100;  // Example width, should be adjusted based on the input
    int height = 100; // Example height, should be adjusted based on the input

    // Allocate memory for the decompressed image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3); // Assuming 3 bytes per pixel (RGB)
    if (dstBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, 0 /* pitch */, height, TJPF_RGB, TJFLAG_FASTDCT);

    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}