#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG handle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == NULL) {
        return 0; // Initialization failed, exit early
    }

    // Ensure that size is not zero to avoid passing NULL to tj3SetICCProfile
    if (size == 0) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tj3SetICCProfile(handle, (unsigned char *)data, size);

    // Clean up
    tj3Destroy(handle);

    return 0;
}