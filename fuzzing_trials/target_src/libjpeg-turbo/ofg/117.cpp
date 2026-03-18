#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the necessary headers for the function-under-test
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

// Define the LLVMFuzzerTestOneInput function
extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Declare and initialize the variables needed for tj3SetCroppingRegion
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    tjregion region;

    // Ensure the handle is not NULL
    if (!handle) {
        return 0;
    }

    // Initialize the region with some values
    region.x = (size > 0) ? data[0] % 256 : 0;
    region.y = (size > 1) ? data[1] % 256 : 0;
    region.w = (size > 2) ? data[2] % 256 : 1; // Width should be non-zero
    region.h = (size > 3) ? data[3] % 256 : 1; // Height should be non-zero

    // Call the function-under-test
    int result = tj3SetCroppingRegion(handle, region);

    // Clean up and free resources
    tj3Destroy(handle);

    return 0;
}