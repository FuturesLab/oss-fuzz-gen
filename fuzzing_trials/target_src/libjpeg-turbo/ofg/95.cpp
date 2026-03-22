#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient for a minimal valid JPEG image
    if (size < 100) { // Arbitrary small size for a minimal JPEG header
        return 0;
    }

    // Define and initialize the parameters for tjDecompressHeader3
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }
    
    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for imageBuffer
    unsigned char *imageBuffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
    if (imageBuffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Decompress the JPEG image into the imageBuffer
    if (tjDecompress2(handle, data, size, imageBuffer, width, 0, height, TJPF_RGB, 0) != 0) {
        free(imageBuffer);
        tjDestroy(handle);
        return 0;
    }

    // Clean up
    free(imageBuffer);
    tjDestroy(handle);

    return 0;
}