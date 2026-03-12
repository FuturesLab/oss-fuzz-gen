#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitDecompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (handle == NULL) {
        return 0;
    }

    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = size;

    int width = 100;  // Example width, should be set according to actual needs
    int height = 100; // Example height, should be set according to actual needs
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // Example flags
    int pitch = 0; // Example pitch, can be set to 0 for default

    // Allocate buffer for decompressed image
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuf == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Fuzz the function tjDecompress2

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 8 of tjDecompress2

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of tjDecompress2
    tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, TJXOPT_CROP, pitch, height, pixelFormat, TJFLAG_BOTTOMUP);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}