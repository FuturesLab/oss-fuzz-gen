#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0;
    }

    // Ensure the size is sufficient to fill a tjregion struct
    if (size < sizeof(tjregion)) {
        tj3Destroy(handle);
        return 0;
    }

    // Initialize a tjregion structure using the input data
    tjregion region;
    region.x = (int)data[0];
    region.y = (int)data[1];
    region.w = (int)data[2];
    region.h = (int)data[3];

    // Call the function-under-test
    tj3SetCroppingRegion(handle, region);

    // Clean up
    tj3Destroy(handle);
    return 0;
}