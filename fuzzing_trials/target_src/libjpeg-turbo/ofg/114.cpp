#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

// Define J16SAMPLE as uint16_t, which is typically used for 16-bit samples
typedef uint16_t J16SAMPLE;

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    // Define dimensions for the output image
    int width = 128;  // Example width
    int height = 128; // Example height

    // Allocate memory for the decompressed image
    J16SAMPLE *outputImage = new J16SAMPLE[width * height * 3]; // Assuming RGB format

    // Call the function-under-test
    int result = tj3Decompress16(handle, data, size, outputImage, width, height);

    // Clean up
    delete[] outputImage;
    tjDestroy(handle);

    return 0;
}