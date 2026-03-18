#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // If initialization fails, return early
    }

    unsigned char *jpegBuf = const_cast<unsigned char *>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 0, height = 0, jpegSubsamp = 0;

    // Call the function-under-test
    int result = tjDecompressHeader2(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp);

    // Clean up the TurboJPEG decompressor
    tjDestroy(handle);

    return 0;
}