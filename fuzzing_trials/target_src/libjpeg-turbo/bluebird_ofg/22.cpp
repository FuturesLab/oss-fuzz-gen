#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor handle

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitDecompress with tjInitTransform

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitTransform with tjInitDecompress
    tjhandle handle = tjInitDecompress();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (handle == nullptr) {
        return 0; // If initialization fails, return immediately
    }

    // Define the width and height for the decompressed image
    int width = 256;  // Example width
    int height = 256; // Example height

    // Allocate memory for the decompressed image buffer
    unsigned char *decompressedImage = new unsigned char[width * height * 3]; // Assuming RGB format

    // Call the function-under-test
    int result = tjDecompress2(handle, data, size, decompressedImage, width, 0 /* pitch */, height, TJPF_RGB, TJFLAG_FASTDCT);

    // Clean up resources
    delete[] decompressedImage;
    tjDestroy(handle);

    return 0;
}