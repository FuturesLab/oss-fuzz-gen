#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0; // Initialization failed
    }

    // Ensure the data is not NULL and size is greater than 0
    if (data == nullptr || size == 0) {
        tj3Destroy(handle);
        return 0;
    }

    // Call the function-under-test
    int result = tj3DecompressHeader(handle, data, size);

    // Clean up
    tj3Destroy(handle);

    return 0;
}