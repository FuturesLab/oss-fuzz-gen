#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Initialize variables for tjEncodeYUV
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Ensure there is enough data to extract parameters
    if (size < 12) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width and height from the data
    int width = (int)data[0] + 1;  // Ensure non-zero
    int height = (int)data[1] + 1; // Ensure non-zero
    int pitch = width * 3;         // Assuming 3 bytes per pixel for RGB

    // Extract pixel format
    int pixelFormat = (int)data[2] % TJ_NUMPF;

    // Allocate memory for the image buffer and YUV buffer
    unsigned char *imgBuf = (unsigned char *)(data + 3);
    unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, 4, height, TJSAMP_444));

    if (yuvBuf == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tjEncodeYUV(handle, imgBuf, width, pitch, height, pixelFormat, yuvBuf, 4, TJSAMP_444);

    // Clean up
    free(yuvBuf);
    tjDestroy(handle);

    return 0;
}