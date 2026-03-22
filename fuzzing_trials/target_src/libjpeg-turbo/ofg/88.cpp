#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Include necessary C headers and wrap them in extern "C"
extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    
    // Function signature for the function-under-test
    int tj3GetICCProfile(tjhandle handle, unsigned char **iccProfile, size_t *iccProfileSize);
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == NULL) {
        return 0;  // Exit if initialization fails
    }

    unsigned char *iccProfile = NULL;
    size_t iccProfileSize = 0;

    // Ensure that the data is not empty
    if (size > 0) {
        // Create a buffer to simulate a JPEG header, as tj3GetICCProfile expects a valid JPEG
        unsigned char jpegHeader[2] = {0xFF, 0xD8}; // SOI marker for JPEG
        unsigned char *jpegData = (unsigned char *)malloc(size + sizeof(jpegHeader));
        if (jpegData == NULL) {
            tj3Destroy(handle);
            return 0;
        }

        // Prepend the JPEG header to the input data
        memcpy(jpegData, jpegHeader, sizeof(jpegHeader));
        memcpy(jpegData + sizeof(jpegHeader), data, size);

        // Decompress the JPEG data to ensure the handle is valid for ICC profile extraction
        int width, height, jpegSubsamp, jpegColorspace;
        if (tjDecompressHeader3(handle, jpegData, size + sizeof(jpegHeader), &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
            // Attempt to call the function-under-test
            int result = tj3GetICCProfile(handle, &iccProfile, &iccProfileSize);

            // Free the ICC profile if it was allocated
            if (iccProfile != NULL) {
                tj3Free(iccProfile);
            }
        }

        free(jpegData);
    }

    // Clean up and destroy the TurboJPEG handle
    tj3Destroy(handle);

    return 0;
}