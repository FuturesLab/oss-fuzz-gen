#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0;
    }

    // Check for minimum size requirement for width, height, and pixel size
    if (size < 12) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width, height, and pixel size from data
    int width = data[0] + 1; // Ensure width is at least 1
    int height = data[1] + 1; // Ensure height is at least 1
    int pixelSize = data[2] % 4 + 1; // Ensure pixel size is between 1 and 4

    // Calculate the input buffer size
    int inputBufferSize = width * height * pixelSize;
    if (size < inputBufferSize + 12) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate and initialize input buffer
    unsigned char *srcBuf = (unsigned char *)malloc(inputBufferSize);
    if (!srcBuf) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(srcBuf, data + 3, inputBufferSize);

    // Allocate output buffer
    unsigned long jpegSize = tjBufSize(width, height, TJSAMP_444);
    unsigned char *jpegBuf = (unsigned char *)malloc(jpegSize);
    if (!jpegBuf) {
        free(srcBuf);
        tjDestroy(handle);
        return 0;
    }

    // Set parameters for compression
    int jpegSubsamp = TJSAMP_444;
    int jpegQual = 75; // Using a standard quality value
    int flags = 0;

    // Call the function-under-test
    int result = tjCompress(handle, srcBuf, width, 0, height, pixelSize, jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

    // Clean up
    free(srcBuf);
    free(jpegBuf);
    tjDestroy(handle);

    return 0;
}