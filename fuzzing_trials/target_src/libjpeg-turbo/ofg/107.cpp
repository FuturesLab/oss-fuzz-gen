#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    unsigned char *yuvBuffer = new unsigned char[size];
    if (yuvBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    int width = 128;  // Example width, adjust as needed
    int height = 128; // Example height, adjust as needed

    int result = tj3DecompressToYUV8(handle, data, size, yuvBuffer, width);

    delete[] yuvBuffer;
    tjDestroy(handle);

    return 0;
}