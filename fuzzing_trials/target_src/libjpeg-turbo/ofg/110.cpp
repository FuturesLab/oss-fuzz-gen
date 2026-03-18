#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Exit if decompression initialization fails
    }

    // Allocate memory for YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3];
    int width = 16; // Example width
    int height = 16; // Example height

    // Calculate the size of each plane and allocate memory
    for (int i = 0; i < 3; i++) {
        strides[i] = width;
        yuvPlanes[i] = (unsigned char *)malloc(strides[i] * height);
        if (yuvPlanes[i] == nullptr) {
            // Clean up and exit if memory allocation fails
            for (int j = 0; j < i; j++) {
                free(yuvPlanes[j]);
            }
            tjDestroy(handle);
            return 0;
        }
    }

    // Call the function-under-test
    tj3DecompressToYUVPlanes8(handle, data, size, yuvPlanes, strides);

    // Clean up
    for (int i = 0; i < 3; i++) {
        free(yuvPlanes[i]);
    }
    tjDestroy(handle);

    return 0;
}