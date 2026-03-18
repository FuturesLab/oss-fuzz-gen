#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle = tjInitCompress();
    if (!handle) {
        return 0;
    }

    // Ensure size is sufficient for at least one pixel
    if (size < sizeof(uint16_t)) { // Assuming J16SAMPLE is uint16_t
        tjDestroy(handle);
        return 0;
    }

    // Initialize J16SAMPLE pointer
    const uint16_t *srcBuf = reinterpret_cast<const uint16_t *>(data);

    // Define image dimensions and pixel format
    int width = 1;  // Minimum width
    int height = size / (sizeof(uint16_t) * width);  // Calculate height based on available data
    int pitch = width * sizeof(uint16_t);
    int pixelFormat = TJPF_RGB;  // Example pixel format

    // Initialize destination buffer and size
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3Compress16(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Clean up
    if (jpegBuf) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}