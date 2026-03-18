#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    int width = 640;
    int height = 480;
    int yuvSize = tjBufSizeYUV2(width, 4, height, TJSAMP_420);
    unsigned char *yuvBuffer = (unsigned char *)malloc(yuvSize);
    if (yuvBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    int flags = 0; // You can choose appropriate flags as needed
    int result = tj3DecompressToYUV8(handle, data, size, yuvBuffer, flags);

    free(yuvBuffer);
    tjDestroy(handle);

    return result;
}