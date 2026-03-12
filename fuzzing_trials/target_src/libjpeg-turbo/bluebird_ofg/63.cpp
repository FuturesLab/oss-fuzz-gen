#include <cstdint>
#include <cstdlib>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
#include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
#include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Define parameters for tjDecompressToYUV2
    const unsigned char *jpegBuf = data;
    unsigned long jpegSize = static_cast<unsigned long>(size);

    // Assuming some arbitrary dimensions for the YUV output
    int width = 128;  // Width of the image
    int height = 128; // Height of the image
    int strides = width; // Strides for YUV planes

    // Allocate memory for the YUV buffer
    unsigned char *yuvBuf = static_cast<unsigned char *>(malloc(width * height * 3));
    if (yuvBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of tjDecompressToYUV2
    int result = tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, TJ_NUMCS, strides, height, 0);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    free(yuvBuf);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjDestroy with tj3GetErrorCode
    tj3GetErrorCode(handle);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}