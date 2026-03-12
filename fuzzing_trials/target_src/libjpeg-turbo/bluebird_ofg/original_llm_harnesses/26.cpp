#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Call the function-under-test
    tjhandle handle = tjInitTransform();

    // Normally, you would perform operations with the handle here
    // For the purpose of this fuzzing harness, we just ensure the function is called

    // Clean up
    if (handle != NULL) {
        tjDestroy(handle);
    }

    return 0;
}