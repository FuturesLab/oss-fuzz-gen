#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Initialize variables for tj3Compress16 function call
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        return 0; // If initialization fails, exit early
    }

    const uint16_t *srcBuf = reinterpret_cast<const uint16_t *>(data);
    int width = 10; // Example width, can be adjusted
    int pitch = 0; // 0 indicates use of width * pixel size
    int height = 10; // Example height, can be adjusted
    int pixelFormat = TJPF_RGB; // Example pixel format, can be adjusted
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    tj3Compress16(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Clean up
    tj3Free(jpegBuf);
    tj3Destroy(handle);

    return 0;
}