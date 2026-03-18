#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    char *errorStr = tjGetErrorStr2(handle);

    // Use the error string in some way to avoid compiler optimizations removing the call
    if (errorStr != NULL) {
        // For example, just check its length
        size_t len = 0;
        while (errorStr[len] != '\0') {
            len++;
        }
    }

    tjDestroy(handle);
    return 0;
}