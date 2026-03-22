#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    if (size < 12) { // Ensure there's enough data for YUV planes
        return 0;
    }

    // Initialize TurboJPEG handle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0;
    }

    // Prepare YUV planes
    const int width = 8;  // Increased width for more meaningful testing
    const int height = 8; // Increased height for more meaningful testing
    const int numPlanes = 3; // Y, U, V planes
    const int planeSizes[] = {width * height, width * height / 4, width * height / 4};
    
    const unsigned char *yuvPlanes[numPlanes];
    unsigned char *allocatedPlanes[numPlanes];

    // Declare all variables before using goto
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Allocate memory for each plane
    size_t offset = 0;
    for (int i = 0; i < numPlanes; i++) {
        allocatedPlanes[i] = (unsigned char *)malloc(planeSizes[i]);
        if (allocatedPlanes[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                free(allocatedPlanes[j]);
            }
            tj3Destroy(handle);
            return 0;
        }
        // Fill the plane with data from the input
        size_t copySize = planeSizes[i] < (size - offset) ? planeSizes[i] : (size - offset);
        memcpy(allocatedPlanes[i], data + offset, copySize);
        offset += copySize;
        yuvPlanes[i] = allocatedPlanes[i];
    }

    // Call the function-under-test
    if (tj3CompressFromYUVPlanes8(handle, yuvPlanes, width, planeSizes, height, &jpegBuf, &jpegSize) == 0 && jpegBuf != nullptr) {
        // Successfully compressed
        tj3Free(jpegBuf);
    }

    // Clean up
    for (int i = 0; i < numPlanes; i++) {
        free(allocatedPlanes[i]);
    }
    tj3Destroy(handle);

    return 0;
}