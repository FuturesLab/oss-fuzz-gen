#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize the parameter for tj3Init
    int init_param = 0; // Using 0 as a default parameter for initialization

    // Call the function-under-test
    tjhandle handle = tj3Init(init_param);

    // If the handle is not NULL, destroy it to avoid memory leaks
    if (handle != NULL) {
        tj3Destroy(handle);
    }

    return 0;
}