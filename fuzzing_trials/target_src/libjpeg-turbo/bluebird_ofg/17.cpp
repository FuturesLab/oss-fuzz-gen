#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (handle == nullptr) {
        return 0; // If initialization fails, exit early
    }

    // Ensure the data size is sufficient for the integer parameter
    if (size < sizeof(int)) {
        tj3Destroy(handle);
        return 0;
    }

    // Extract an integer from the input data
    int param = *reinterpret_cast<const int*>(data);

    // Call the function-under-test
    int result = tj3Get(handle, param);

    // Clean up
    tj3Destroy(handle);

    return 0;
}