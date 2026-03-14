#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Initialization failed, return early
    }

    // Assuming J16SAMPLE is a typedef or define in the included headers
    // Adjust the type to uint16_t if J16SAMPLE is not defined
    const uint16_t *srcBuf = reinterpret_cast<const uint16_t *>(data);
    int width = 16;  // Example width
    int pitch = 16 * sizeof(uint16_t);  // Example pitch, adjusted for 16-bit samples
    int height = 16; // Example height
    int jpegSubsamp = TJSAMP_444; // Example subsampling
    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    // Call the function-under-test
    int result = tj3Compress16(handle, srcBuf, width, pitch, height, jpegSubsamp, &jpegBuf, &jpegSize);

    // Clean up
    if (jpegBuf != nullptr) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return 0;
}