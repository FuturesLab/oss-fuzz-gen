#include <cstdint>
#include <cstdlib>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
#include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
#include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 7 of tjDecompressToYUV2
    int result = tjDecompressToYUV2(handle, jpegBuf, jpegSize, yuvBuf, width, strides, height, TJFLAG_FORCESSE2);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjDecompressToYUV2 to tjPlaneWidth

    int ret_tjPlaneWidth_tucbx = tjPlaneWidth(result, TJFLAG_FORCESSE, TJFLAG_STOPONWARNING);
    if (ret_tjPlaneWidth_tucbx < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}