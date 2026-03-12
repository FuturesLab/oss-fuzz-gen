#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    if (size < 10) {
        return 0; // Ensure there's enough data for the parameters
    }

    // Initialize parameters for tjCompress
    tjhandle handle = tjInitCompress();
    unsigned char *srcBuf = (unsigned char *)data;
    int width = 2;  // Minimal width for testing
    int pitch = 2;  // Minimal pitch for testing
    int height = 2; // Minimal height for testing
    int pixelFormat = TJPF_RGB; // Use a valid pixel format
    unsigned char *jpegBuf = nullptr; // Output buffer
    unsigned long jpegSize = 0; // Size of the JPEG buffer
    int jpegSubsamp = TJSAMP_444; // Use a valid subsampling option
    int jpegQual = 75; // A typical quality value
    int flags = 0; // No special flags

    // Call the function-under-test
    tjCompress(handle, srcBuf, width, pitch, height, pixelFormat, jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

    // Clean up
    tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}