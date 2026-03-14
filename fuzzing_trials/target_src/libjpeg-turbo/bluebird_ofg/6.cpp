#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    tjhandle handle = tjInitCompress();
    if (handle == NULL) {
        return 0;
    }

    // Ensure the input data is large enough for width, height, and pixel format
    if (size < 12) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width, height, and pixel format from the input data
    int width = static_cast<int>(data[0]) + 1; // Avoid zero width
    int height = static_cast<int>(data[1]) + 1; // Avoid zero height
    int pixelFormat = static_cast<int>(data[2]) % TJ_NUMPF;

    // Calculate the required buffer size for the source image
    int pitch = width * tjPixelSize[pixelFormat];
    const unsigned char *srcBuffer = data + 3;
    if (size < (size_t)(3 + pitch * height)) {
        tjDestroy(handle);
        return 0;
    }

    // Prepare the YUV planes
    unsigned char *yuvPlanes[3];
    int strides[3];
    int subsamp = TJSAMP_420; // Use a common subsampling format

    // Calculate the size of each plane and allocate memory
    for (int i = 0; i < 3; i++) {
        strides[i] = tjPlaneWidth(i, width, subsamp);
        int planeSize = tjPlaneSizeYUV(i, width, strides[i], height, subsamp);
        yuvPlanes[i] = new unsigned char[planeSize];
    }

    // Call the function-under-test
    int result = tjEncodeYUVPlanes(handle, srcBuffer, width, pitch, height, pixelFormat, yuvPlanes, strides, subsamp, 0);

    // Clean up
    for (int i = 0; i < 3; i++) {
        delete[] yuvPlanes[i];
    }
    tjDestroy(handle);

    return result;
}