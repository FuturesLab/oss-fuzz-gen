#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Call the function-under-test
    char *errorStr = tj3GetErrorStr(handle);

    // Ensure the errorStr is not null and do something with it
    if (errorStr != nullptr) {
        // For example, print the error string (in a real fuzzing scenario, you might log it)
        // printf("Error: %s\n", errorStr);
    }

    // Clean up the handle
    tjDestroy(handle);

    return 0;
}