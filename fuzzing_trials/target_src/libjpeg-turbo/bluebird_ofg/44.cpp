#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include for memset

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize the integer parameter for tjInitCompress function
    int initParam = TJPF_RGB; // Use a valid pixel format

    // Call the function-under-test with the initialized parameter
    tjhandle handle = tjInitCompress();

    // Check if the handle is valid
    if (handle != NULL) {
        // Perform operations with the handle
        unsigned char *jpegBuf = NULL;  // Buffer for the compressed image
        unsigned long jpegSize = 0;     // Size of the JPEG image

        // Ensure that data is large enough to be used as an image buffer
        if (size >= 30000) { // Example size check for a 100x100 RGB image
            int width = 100;                // Example width
            int height = 100;               // Example height
            int pitch = width * 3;          // Number of bytes per row (3 bytes per pixel for RGB)
            int jpegSubsamp = TJSAMP_444;   // Example subsampling
            int jpegQual = 75;              // Example quality

            // Compress the input data
            if (tjCompress2(handle, (unsigned char *)data, width, pitch, height, initParam, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, 0) == 0) {
                // Successfully compressed, now free the buffer
                tjFree(jpegBuf);
            }
        }

        // Clean up the handle

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from tjInitCompress to tj3Set
    int mcazmxbv = 64;
    tjscalingfactor* ret_tjGetScalingFactors_ptryx = tjGetScalingFactors(&mcazmxbv);
    if (ret_tjGetScalingFactors_ptryx == NULL){
    	return 0;
    }

    int ret_tj3Set_qqfyv = tj3Set(handle, mcazmxbv, TJFLAG_FASTDCT);
    if (ret_tj3Set_qqfyv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        tjDestroy(handle);
    }

    return 0;
}