#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>  // Include this for stderr

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure there's enough data for a small YUV image
    if (size < 48) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Prepare YUV planes
    const unsigned char* yuvPlanes[3];
    int strides[3];

    // Assume a minimum size for each plane
    int width = 16;
    int height = 16;

    // Ensure that the data size is sufficient for the YUV planes
    int yPlaneSize = width * height;
    int uvPlaneSize = (width / 2) * (height / 2);

    if (size < yPlaneSize + 2 * uvPlaneSize) {
        tjDestroy(handle);
        return 0;
    }

    // Initialize YUV planes with the input data
    yuvPlanes[0] = data;
    yuvPlanes[1] = data + yPlaneSize;
    yuvPlanes[2] = data + yPlaneSize + uvPlaneSize;

    // Set strides according to the YUV 4:2:0 format
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    // Compressed image buffer
    unsigned char* jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    // Quality and subsampling (arbitrarily chosen for fuzzing)
    int quality = 50;
    int subsamp = TJSAMP_420;

    // Call the function-under-test
    int result = tjCompressFromYUVPlanes(handle, yuvPlanes, width, strides, width, height, &jpegBuf, &jpegSize, subsamp, quality);

    // Check if the compression was successful
    if (result == 0 && jpegBuf != nullptr && jpegSize > 0) {
        // Successfully compressed, can further process jpegBuf if needed
    } else {
        // Log the error for debugging purposes
        const char* errorMsg = tjGetErrorStr();
        if (errorMsg) {
            fprintf(stderr, "Compression failed: %s\n", errorMsg);
        }
    }

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}