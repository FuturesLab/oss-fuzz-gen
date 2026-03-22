#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    typedef uint16_t J16SAMPLE; // Assuming J16SAMPLE is a 16-bit sample type
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for a minimal JPEG header
    if (size < 2 || data[0] != 0xFF || data[1] != 0xD8) {
        // Not a valid JPEG file header
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    // Ensure the output buffer is large enough to hold the decompressed image
    J16SAMPLE *outputBuffer = (J16SAMPLE *)malloc(width * height * 3 * sizeof(J16SAMPLE));
    if (outputBuffer == NULL) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tjDecompress2(handle, data, size, (unsigned char *)outputBuffer, width, 0 /* pitch */, height, TJPF_RGB, TJFLAG_FASTDCT);

    // Clean up
    free(outputBuffer);
    tjDestroy(handle);

    return 0;
}