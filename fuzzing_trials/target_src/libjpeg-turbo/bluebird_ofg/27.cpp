#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitCompress();  // Initialize a TurboJPEG compressor handle
    if (handle == NULL) {
        return 0;  // If initialization fails, return early
    }

    // Ensure that the data is not NULL and size is greater than zero
    if (data != NULL && size > 0) {
        // Call the function-under-test with the provided data
        int result = tj3SetICCProfile(handle, (unsigned char *)data, size);
    }

    tjDestroy(handle);  // Clean up and destroy the TurboJPEG handle
    return 0;
}