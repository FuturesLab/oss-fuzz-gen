#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Initialize an integer parameter for tj3Init
    int initParam = 0; // Typically, 0 is used for default initialization

    // Call the function-under-test
    tjhandle handle = tj3Init(initParam);

    // Check if the handle is valid and perform cleanup
    if (handle != nullptr) {
        tj3Destroy(handle);
    }

    return 0;
}