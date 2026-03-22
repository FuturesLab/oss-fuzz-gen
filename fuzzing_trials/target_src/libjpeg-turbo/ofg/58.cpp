#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there's enough data to avoid unnecessary processing
    }

    tjhandle handle = tjInitCompress(); // Initialize a TurboJPEG compressor instance

    if (handle == NULL) {
        return 0; // If initialization fails, return early
    }

    // Use the input data to create a small image buffer
    int width = 1;
    int height = 1;
    int subsamp = TJSAMP_444;
    int jpegQual = 75; // Quality of JPEG compression
    unsigned long jpegSize = 0;
    unsigned char *jpegBuf = NULL;

    // Compress the image
    int result = tjCompress2(handle, data, width, 0, height, TJPF_RGB,
                             &jpegBuf, &jpegSize, subsamp, jpegQual, TJFLAG_FASTDCT);

    if (result == 0 && jpegBuf != NULL) {
        // Normally, you would do something with jpegBuf, but since this is a fuzzing harness,
        // we're just testing for crashes or memory corruption, so we don't need to use it.
        tjFree(jpegBuf); // Free the JPEG buffer
    }

    tjDestroy(handle); // Clean up the TurboJPEG instance

    return 0;
}