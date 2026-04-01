#include <cstddef>
#include <cstdint>
#include <cstdlib> // for std::malloc and std::free
#include <algorithm> // for std::min

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to proceed
    }

    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Failed to initialize
    }

    // Dynamically determine width and height based on input size
    int width = std::min(static_cast<int>(size / 3), 256); // Limit to 256 for practical reasons
    int height = std::min(static_cast<int>(size / 3), 256);

    // Prepare YUV planes
    const unsigned char *yuvPlanes[3];
    int planeSizes[3];

    // Calculate plane sizes and assign data
    planeSizes[0] = width * height; // Y plane size
    planeSizes[1] = width * height / 4; // U plane size
    planeSizes[2] = width * height / 4; // V plane size

    if (size < static_cast<size_t>(planeSizes[0] + planeSizes[1] + planeSizes[2])) {
        tjDestroy(handle);
        return 0; // Not enough data for YUV planes
    }

    yuvPlanes[0] = data; // Y plane
    yuvPlanes[1] = data + planeSizes[0]; // U plane
    yuvPlanes[2] = data + planeSizes[0] + planeSizes[1]; // V plane

    // Prepare the destination buffer
    int pixelFormat = TJPF_RGB; // Output pixel format
    unsigned char *dstBuffer = new unsigned char[width * height * tjPixelSize[pixelFormat]];

    // Call the function-under-test
    tj3DecodeYUVPlanes8(handle, yuvPlanes, planeSizes, dstBuffer, width, 0, height, pixelFormat);

    // Clean up
    delete[] dstBuffer;
    tjDestroy(handle);

    return 0;
}