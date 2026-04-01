#include <stddef.h>
#include <stdint.h>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Assuming J16SAMPLE is a 16-bit sample, using uint16_t as a substitute
    if (size < sizeof(uint16_t)) return 0;

    // Initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) return 0;

    const uint16_t *srcBuf = reinterpret_cast<const uint16_t *>(data);
    int width = 1;  // Minimum width
    int height = 1; // Minimum height
    int pitch = width * sizeof(uint16_t);
    int pixelFormat = TJPF_RGB; // Assuming RGB format
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    tj3Compress16(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}