#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there's enough data for a minimal JPEG header
    }

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Attempt to decompress the input data
    int width, height, jpegSubsamp, jpegColorspace;
    unsigned char *decompressedImage = NULL;
    int flags = 0;

    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Allocate memory for the decompressed image
        decompressedImage = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (decompressedImage != NULL) {
            // Decompress the image
            tjDecompress2(handle, data, size, decompressedImage, width, 0, height, TJPF_RGB, flags);
            free(decompressedImage);
        }
    }

    // Clean up resources
    tjDestroy(handle);

    return 0;
}