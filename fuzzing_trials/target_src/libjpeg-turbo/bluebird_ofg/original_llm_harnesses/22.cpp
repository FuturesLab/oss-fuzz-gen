#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Declare and initialize variables for tjEncodeYUVPlanes
    tjhandle handle = tjInitCompress();  // Initialize TurboJPEG compressor
    if (handle == nullptr) {
        return 0;  // If initialization fails, return early
    }

    // Ensure that the input size is sufficient for width, height, and pixel format
    if (size < 12) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width, height, and pixel format from the data
    int width = (int)data[0] + 1;  // Ensure width is at least 1
    int height = (int)data[1] + 1; // Ensure height is at least 1
    int pixelFormat = (int)data[2] % TJ_NUMPF; // Ensure valid pixel format

    // Calculate the pitch (row stride) for the image
    int pitch = width * tjPixelSize[pixelFormat];

    // Allocate memory for YUV planes
    unsigned char* yuvPlanes[3];
    int yuvStrides[3] = { width, width / 2, width / 2 }; // Typical strides for Y, U, and V planes

    for (int i = 0; i < 3; i++) {
        yuvPlanes[i] = new unsigned char[width * height / ((i == 0) ? 1 : 4)];
    }

    // Call the function under test
    int result = tjEncodeYUVPlanes(handle, data, width, pitch, height, pixelFormat, yuvPlanes, yuvStrides, 0, TJFLAG_FASTDCT);

    // Clean up
    for (int i = 0; i < 3; i++) {
        delete[] yuvPlanes[i];
    }
    tjDestroy(handle);

    return 0;
}