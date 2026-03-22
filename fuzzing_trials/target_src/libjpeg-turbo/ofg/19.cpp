#include <cstddef>
#include <cstdint>

extern "C" {
#include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Initialization failed, return early
    }

    // Ensure that data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        tjDestroy(handle);
        return 0;
    }

    // Call the function-under-test
    tj3DecompressHeader(handle, data, size);

    // Clean up
    tjDestroy(handle);

    return 0;
}