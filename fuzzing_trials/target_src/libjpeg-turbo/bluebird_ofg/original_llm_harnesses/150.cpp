#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0;
    }

    // Ensure the size is sufficient for at least one pixel
    if (size < sizeof(uint16_t)) {
        tjDestroy(handle);
        return 0;
    }

    // Set up input image parameters
    int width = 1;  // Minimal width
    int height = 1; // Minimal height
    int pitch = width * sizeof(uint16_t);
    int pixelFormat = TJPF_RGB;

    // Allocate memory for the compressed image
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3Compress16(handle, (const uint16_t *)data, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Free allocated resources
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return result;
}