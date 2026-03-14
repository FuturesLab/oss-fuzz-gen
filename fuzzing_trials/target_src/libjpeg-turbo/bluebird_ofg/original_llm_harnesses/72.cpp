#include <stddef.h>
#include <stdint.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"

    // Forward declaration of the function under test
    int tj3Compress16(tjhandle handle, const unsigned short *srcBuf, int width, int pitch, int height, int pixelFormat, unsigned char **jpegBuf, size_t *jpegSize);
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Ensure the data size is sufficient for width, height, and pixel format
    if (size < sizeof(int) * 3) {
        tjDestroy(handle);
        return 0;
    }

    // Extract width, height, and pixelFormat from data
    int width = static_cast<int>(data[0]) + 1; // Avoid zero width
    int height = static_cast<int>(data[1]) + 1; // Avoid zero height
    int pixelFormat = static_cast<int>(data[2]) % TJ_NUMPF; // Valid pixel format

    // Calculate pitch (row size in bytes)
    int pitch = width * tjPixelSize[pixelFormat];

    // Ensure the data size is sufficient for the image buffer
    if (size < sizeof(int) * 3 + pitch * height) {
        tjDestroy(handle);
        return 0;
    }

    // Point srcBuf to the appropriate location in data
    const unsigned short *srcBuf = reinterpret_cast<const unsigned short *>(data + sizeof(int) * 3);

    // Prepare output buffer
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function under test
    tj3Compress16(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}