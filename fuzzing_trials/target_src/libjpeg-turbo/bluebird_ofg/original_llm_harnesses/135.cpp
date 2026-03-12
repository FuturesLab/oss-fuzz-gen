extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No data to process
    }

    // Initialize tjhandle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // Initialization failed, exit early
    }

    // Call the function-under-test
    char *errorStr = tj3GetErrorStr(handle);
    if (errorStr == nullptr) {
        tjDestroy(handle);
        return 0; // No error string, exit early
    }

    // Cleanup
    tjDestroy(handle);

    return 0;
}