#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0;
    }

    // Assuming YUV format with 3 planes (Y, U, V)
    const unsigned char *yuvPlanes[3];
    int strides[3] = {0, 0, 0};
    int width = 16;  // Example width
    int height = 16; // Example height

    // Allocate memory for YUV planes
    size_t planeSize = width * height;
    unsigned char *planeData = new unsigned char[planeSize * 3];
    yuvPlanes[0] = planeData;                     // Y plane
    yuvPlanes[1] = planeData + planeSize;         // U plane
    yuvPlanes[2] = planeData + 2 * planeSize;     // V plane

    // Fill the planes with data from the fuzzer input
    size_t copySize = (size < planeSize * 3) ? size : planeSize * 3;
    for (size_t i = 0; i < copySize; ++i) {
        planeData[i] = data[i];
    }

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    int jpegSubsamp = TJSAMP_420; // Example subsampling
    int flags = 0;                // Example flags

    // Call the function-under-test
    tjCompressFromYUVPlanes(handle, yuvPlanes, width, strides, height, jpegSubsamp, &jpegBuf, &jpegSize, 100, flags);

    // Clean up
    tjFree(jpegBuf);
    delete[] planeData;
    tjDestroy(handle);

    return 0;
}