#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    int value = 0;

    if (handle == NULL) {
        return 0;
    }

    if (size > 0) {
        // Use the first byte of data as an integer input
        value = static_cast<int>(data[0]);
    }

    // Call the function-under-test
    int result = tj3Get(handle, value);

    // Clean up
    tjDestroy(handle);

    return 0;
}