#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Initialize variables for tjDecompressToYUV2
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = (unsigned long)size;

    // Allocate memory for the YUV buffer
    int width = 640;  // Example width
    int height = 480; // Example height
    int subsamp = TJSAMP_420; // Example subsampling
    int flags = 0; // No flags

    unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, subsamp));
    if (yuvBuf == nullptr) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjDestroy with tj3GetErrorCode
        tj3GetErrorCode(handle);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjDecompressToYUV2
    tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, 4, height, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Cleanup
    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}