#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

// Ensure the function-under-test is called within LLVMFuzzerTestOneInput
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Call the function-under-test
    tjhandle handle = tjInitCompress();

    // Check if the handle was successfully created
    if (handle != nullptr) {
        // Perform any additional operations if necessary

        // Destroy the handle after use to avoid resource leaks
        tjDestroy(handle);
    }

    return 0;
}