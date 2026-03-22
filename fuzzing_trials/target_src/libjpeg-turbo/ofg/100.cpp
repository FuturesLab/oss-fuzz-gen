#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    int numScalingFactors = 0;

    // Call the function-under-test with a non-null pointer
    tjscalingfactor *scalingFactors = tjGetScalingFactors(&numScalingFactors);

    // Use the scalingFactors and numScalingFactors to explore the results
    if (scalingFactors != nullptr && numScalingFactors > 0 && size > 0) {
        for (int i = 0; i < numScalingFactors; ++i) {
            // Access scalingFactors[i].num and scalingFactors[i].denom
            volatile int num = scalingFactors[i].num;
            volatile int denom = scalingFactors[i].denom;
            // Use volatile to prevent compiler optimizations that remove these accesses

            // Additional code to increase code coverage
            // Create a buffer to hold decompressed image
            unsigned long jpegSize = size;
            unsigned char *jpegBuf = (unsigned char *)malloc(jpegSize);
            if (jpegBuf == nullptr) {
                return 0; // Failed to allocate memory
            }
            memcpy(jpegBuf, data, size);

            // Initialize decompressor
            tjhandle tjInstance = tjInitDecompress();
            if (tjInstance != nullptr) {
                int width, height, jpegSubsamp, jpegColorspace;

                // Decompress the image
                if (tjDecompressHeader3(tjInstance, jpegBuf, jpegSize, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
                    // Allocate buffer for decompressed image
                    unsigned char *imgBuf = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
                    if (imgBuf != nullptr) {
                        // Perform decompression
                        tjDecompress2(tjInstance, jpegBuf, jpegSize, imgBuf, width, 0 /* pitch */, height, TJPF_RGB, TJFLAG_FASTDCT);
                        free(imgBuf);
                    }
                }
                tjDestroy(tjInstance);
            }
            free(jpegBuf);
        }
    }

    return 0;
}