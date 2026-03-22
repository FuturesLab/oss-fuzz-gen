#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    int tj3SetCroppingRegion(tjhandle handle, tjregion region);
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size < sizeof(tjregion)) {
        return 0; // Not enough data to fill tjregion
    }

    // Initialize tjhandle
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (handle == nullptr) {
        return 0; // Initialization failed
    }

    // Initialize tjregion with data
    tjregion region;
    memcpy(&region, data, sizeof(tjregion));

    // Validate region dimensions to ensure they are positive
    region.w = (abs(region.w) % 1000) + 1; // Ensure width is at least 1
    region.h = (abs(region.h) % 1000) + 1; // Ensure height is at least 1

    // Ensure region is within valid bounds
    region.x = abs(region.x) % 1000; // Limit x to a reasonable value
    region.y = abs(region.y) % 1000; // Limit y to a reasonable value

    // Call the function-under-test
    if (tj3SetCroppingRegion(handle, region) != 0) {
        // Handle error if needed, e.g., log or return
    }

    // Clean up
    tj3Destroy(handle);

    return 0;
}