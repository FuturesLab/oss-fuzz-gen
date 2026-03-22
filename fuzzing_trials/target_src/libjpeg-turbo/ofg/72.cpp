#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        return 0;
    }

    // Ensure the input data is large enough to contain at least one pixel
    if (size < 3) {
        tj3Destroy(handle);
        return 0;
    }

    // Derive image dimensions from input data
    int width = data[0] % 256 + 1;  // Width derived from first byte, ensuring minimum width of 1
    int height = data[1] % 256 + 1; // Height derived from second byte, ensuring minimum height of 1

    // Check if the data size is sufficient for the derived dimensions
    if (size < width * height * 3) {
        tj3Destroy(handle);
        return 0;
    }

    int pitch = width * 3; // Assuming 3 bytes per pixel for RGB
    int subsamp = TJSAMP_444; // Using 4:4:4 subsampling
    int colorspace = TJCS_RGB; // Assuming input data is in RGB colorspace

    // Allocate memory for compressed image
    unsigned char *compressedImage = NULL;
    size_t compressedSize = 0;

    // Call the function-under-test
    int result = tjCompress2(handle, data, width, pitch, height, colorspace, &compressedImage, &compressedSize, subsamp, 100, TJFLAG_FASTDCT);

    // Free allocated resources
    if (compressedImage) {
        tjFree(compressedImage);
    }
    tjDestroy(handle);

    return 0;
}