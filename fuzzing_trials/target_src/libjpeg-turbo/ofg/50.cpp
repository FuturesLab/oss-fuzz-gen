#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to form a valid ICC profile
    }

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == NULL) {
        return 0; // Initialization failed, exit early
    }

    // Allocate memory for the ICC profile
    unsigned char *iccProfile = (unsigned char *)malloc(size);
    if (iccProfile == NULL) {
        tj3Destroy(handle);
        return 0; // Memory allocation failed, exit early
    }

    // Copy the input data to the ICC profile buffer
    memcpy(iccProfile, data, size);

    // Call the function-under-test
    int result = tj3SetICCProfile(handle, iccProfile, size);

    // Check if the function call was successful to ensure coverage
    if (result == 0) {
        // Perform additional operations to further increase coverage
        unsigned char *jpegBuf = NULL;
        size_t jpegSize = 0;
        int width = 100; // Example width
        int height = 100; // Example height
        int pixelFormat = TJPF_RGB; // Pixel format for tj3Compress8

        // Create a dummy image buffer with valid content to ensure compression
        unsigned char *imageBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
        if (imageBuf != NULL) {
            // Fill the image buffer with some pattern or data
            for (int i = 0; i < width * height * tjPixelSize[pixelFormat]; i++) {
                imageBuf[i] = (unsigned char)(i % 256);
            }

            // Compress the image to JPEG
            result = tj3Compress8(handle, imageBuf, width, 0, height, pixelFormat, &jpegBuf, &jpegSize);
            if (result == 0) {
                // Successfully compressed, check jpegBuf and jpegSize for further operations
                if (jpegBuf != NULL && jpegSize > 0) {
                    // Process the JPEG buffer to ensure it is not null and has size
                    // This ensures that the function under test is effectively utilized
                }
                tj3Free(jpegBuf); // Free the buffer allocated by libjpeg-turbo
            }

            free(imageBuf);
        }
    }

    // Clean up
    free(iccProfile);
    tj3Destroy(handle);

    return 0;
}