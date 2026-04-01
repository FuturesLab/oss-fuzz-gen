#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

// Define J16SAMPLE if not defined in the included headers
#ifndef J16SAMPLE
typedef unsigned short J16SAMPLE;
#endif

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    if (size < 2 * sizeof(J16SAMPLE)) {
        return 0; // Not enough data to form even a single pixel
    }

    // Initialize variables for the function call
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0; // Early exit if handle initialization fails
    }

    const J16SAMPLE *srcBuf = reinterpret_cast<const J16SAMPLE *>(data);

    // Dynamically determine width and height based on input size
    int width = 16; // Example fixed width
    int pitch = width * sizeof(J16SAMPLE);
    int height = (size / pitch) > 0 ? (size / pitch) : 1; // Ensure at least 1 row

    int pixelFormat = TJPF_RGB; // Example pixel format

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0; // Correct type for jpegSize

    // Call the function-under-test
    int result = tjCompress2(handle, reinterpret_cast<const unsigned char *>(srcBuf), width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, TJSAMP_444, 100, TJFLAG_FASTDCT);

    // Check if the compression was successful
    if (result == 0 && jpegSize > 0) {
        // Optionally, process the jpegBuf or check its contents
    }

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}