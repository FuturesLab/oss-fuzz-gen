#include <stddef.h>
#include <stdint.h>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == NULL) {
        return 0;
    }

    int width = 0, height = 0, jpegSubsamp = 0, jpegColorspace = 0;

    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (dstBuf != NULL) {
            int pitch = width * tjPixelSize[TJPF_RGB];
            tj3Decompress8(handle, data, size, dstBuf, pitch, TJPF_RGB);
            free(dstBuf);
        }
    }

    tj3Destroy(handle);
    return 0;
}