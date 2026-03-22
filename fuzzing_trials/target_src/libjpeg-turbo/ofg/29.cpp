#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure the data size is at least 4 bytes to extract an integer
    if (size < 4) {
        return 0;
    }

    // Extract an integer from the data to use as the parameter for tj3Init
    int initParam = (int)(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

    // Call the function-under-test
    tjhandle handle = tj3Init(initParam);

    // If handle is not NULL, destroy it to prevent resource leaks
    if (handle != NULL) {
        tj3Destroy(handle);
    }

    return 0;
}