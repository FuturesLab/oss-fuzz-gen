#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Declare and initialize tjhandle and tjregion
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    tjregion region;
    // Ensure the region is initialized with non-zero values
    region.x = size > 0 ? data[0] % 256 : 1;
    region.y = size > 1 ? data[1] % 256 : 1;
    region.w = size > 2 ? data[2] % 256 : 1;
    region.h = size > 3 ? data[3] % 256 : 1;

    // Call the function-under-test
    tj3SetCroppingRegion(handle, region);

    // Clean up
    tjDestroy(handle);

    return 0;
}