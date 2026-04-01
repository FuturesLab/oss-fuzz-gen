#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> // Include this for FILE type

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/jpeglib.h" // Include this for JSAMPLE
}

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    if (size < sizeof(JSAMPLE)) { // Corrected to use JSAMPLE
        return 0; // Not enough data to form a valid input
    }

    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0; // Failed to initialize compressor
    }

    // Prepare input parameters
    const JSAMPLE *srcBuf = (const JSAMPLE *)data; // Corrected to use JSAMPLE
    int width = 1;   // Minimum width
    int height = 1;  // Minimum height
    int pitch = width * sizeof(JSAMPLE); // Corrected to use JSAMPLE
    int pixelFormat = TJPF_RGB;

    unsigned char *jpegBuf = NULL;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, TJSAMP_444, 100, TJFLAG_FASTDCT);

    // Free resources
    if (jpegBuf != NULL) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}