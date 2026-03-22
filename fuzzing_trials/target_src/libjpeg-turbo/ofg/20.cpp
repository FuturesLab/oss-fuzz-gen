#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize the TurboJPEG decompressor
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, exit the fuzzer
    }

    // Call the function-under-test
    int result = tj3DecompressHeader(handle, data, size);

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}