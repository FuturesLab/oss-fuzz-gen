extern "C" {
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG decompressor handle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Initialization failed, exit early
    }

    // Define the width and height for the output image
    int width = 64;  // Example width
    int height = 64; // Example height

    // Calculate the size of the decompressed image buffer
    int pixelFormat = TJPF_RGB;
    int pitch = width * tjPixelSize[pixelFormat];
    size_t bufferSize = width * height * tjPixelSize[pixelFormat];

    // Allocate memory for the decompressed image buffer
    unsigned char *decompressedImage = (unsigned char *)malloc(bufferSize);
    if (decompressedImage == nullptr) {
        tjDestroy(handle);
        return 0; // Memory allocation failed, exit early
    }

    // Call the function-under-test
    int result = tjDecompress2(handle, data, size, decompressedImage, width, pitch, height, pixelFormat, 0);

    // Free allocated resources
    free(decompressedImage);
    tjDestroy(handle);

    return 0;
}