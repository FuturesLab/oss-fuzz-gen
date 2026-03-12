#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        return 0; // Initialization failed, exit early
    }

    unsigned char *iccProfile = nullptr;
    size_t iccProfileSize = 0;

    // Call the function-under-test
    int result = tj3GetICCProfile(handle, &iccProfile, &iccProfileSize);

    // Clean up
    if (iccProfile) {
        tjFree(iccProfile);
    }
    tjDestroy(handle);

    return 0;
}