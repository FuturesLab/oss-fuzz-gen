#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Initialize a TurboJPEG decompressor handle
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int errorCode = tjGetErrorCode(handle);

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}