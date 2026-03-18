#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    char *errorStr = tjGetErrorStr2(handle);

    // Use the errorStr to prevent compiler optimizations
    if (errorStr != NULL) {
        volatile char *volatileErrorStr = errorStr;
        (void)volatileErrorStr;
    }

    tjDestroy(handle);
    return 0;
}