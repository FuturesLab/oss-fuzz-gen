#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;  // If initialization fails, exit early
    }

    // Ensure size is sufficient for the test
    if (size < sizeof(int)) {
        tjDestroy(handle);
        return 0;
    }

    // Extract an integer from the data
    int param = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    int result = tj3Get(handle, param);

    // Clean up
    tjDestroy(handle);

    return 0;
}