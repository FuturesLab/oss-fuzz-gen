#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0;  // Not enough data for a valid JPEG header
    }

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == NULL) {
        return 0;
    }

    // Allocate a buffer for decompressed image
    unsigned char *dstBuf = NULL;
    int width, height, jpegSubsamp, jpegColorspace;

    // Attempt to decompress the JPEG image
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        int pixelFormat = TJPF_RGB;  // Choose a pixel format
        int pitch = width * tjPixelSize[pixelFormat];
        dstBuf = (unsigned char *)malloc(pitch * height);

        if (dstBuf != NULL) {
            tj3Decompress8(handle, data, size, dstBuf, pitch, pixelFormat);  // Corrected function call with 6 arguments
            free(dstBuf);
        }
    }

    tj3Destroy(handle);
    return 0;
}