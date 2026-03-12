#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tjhandle handle;
    int param1, param2;

    // Initialize the TurboJPEG handle
    handle = tjInitCompress();
    if (handle == nullptr) {
        return 0; // Exit if initialization fails
    }

    // Ensure size is sufficient to extract two integers
    if (size < 2 * sizeof(int)) {
        tjDestroy(handle);
        return 0;
    }

    // Extract two integers from the data
    param1 = static_cast<int>(data[0]);
    param2 = static_cast<int>(data[1]);

    // Call the function-under-test
    int result = tj3Set(handle, param1, param2);

    // Clean up
    tjDestroy(handle);

    return 0;
}