#include <stddef.h>
#include <stdint.h>
#include <stdlib.h> // For malloc and free

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to be used meaningfully
    if (size < sizeof(int)) {
        return 0;
    }

    int numScalingFactors = 0;

    // Call the function-under-test
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);

    // Check if scalingFactors is not NULL and numScalingFactors is greater than 0
    if (scalingFactors != NULL && numScalingFactors > 0) {
        // Allocate memory for a dummy image buffer
        int width = 100;
        int height = 100;
        int pixelFormat = TJPF_RGB;
        unsigned char *dummyImage = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);

        if (dummyImage != NULL) {
            // Create a decompressor instance
            tjhandle decompressor = tj3Init(TJINIT_DECOMPRESS);

            if (decompressor != NULL) {
                // Perform a dummy decompression operation
                tjDecompressHeader(decompressor, (unsigned char *)data, size, &width, &height);
                tjDecompress(decompressor, (unsigned char *)data, size, dummyImage, width, 0, height, pixelFormat, TJFLAG_FASTDCT);

                // Clean up the decompressor
                tjDestroy(decompressor);
            }

            // Free the dummy image buffer
            free(dummyImage);
        }

        // Iterate over the scaling factors and perform some trivial operations
        for (int i = 0; i < numScalingFactors; i++) {
            int num = scalingFactors[i].num;
            int denom = scalingFactors[i].denom;

            // Perform some basic calculations to ensure full execution
            if (denom != 0) {
                volatile double scale = static_cast<double>(num) / denom;
                (void)scale; // Use volatile to prevent compiler optimization
            }
        }
    }

    return 0;
}