#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there is enough data for the input parameters
    }

    // Initialize tjhandle
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Failed to initialize, exit early
    }

    // Extract parameters from the data
    int width = (int)data[0] + 1;  // Ensure width is at least 1
    int height = (int)data[1] + 1; // Ensure height is at least 1
    int pixelFormat = (int)data[2] % TJ_NUMPF;
    int quality = (int)data[3] % 101; // Quality range 0-100
    int flags = (int)data[4] % (TJFLAG_ACCURATEDCT + 1);

    // Prepare input image buffer
    int pixelSize = tjPixelSize[pixelFormat];
    size_t imageSize = width * height * pixelSize;
    if (size < imageSize + 10) {
        tjDestroy(handle);
        return 0; // Not enough data for the image, exit early
    }
    const unsigned char *srcBuf = data + 10;

    // Prepare output buffer
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of tjCompress2
    int result = tjCompress2(handle, srcBuf, width, 0, TJ_NUMXOP, pixelFormat, &jpegBuf, &jpegSize, TJSAMP_444, quality, flags);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}