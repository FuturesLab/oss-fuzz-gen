#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize TurboJPEG handle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Use the first byte of data as an integer parameter for tj3Get
    int param = static_cast<int>(data[0]);

    // Call the function-under-test
    int result = tj3Get(handle, param);

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}