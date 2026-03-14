#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_343(const uint8_t *data, size_t size) {
    cmsHANDLE it8Handle = NULL;
    cmsUInt32Number tableCount;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Initialize the IT8 handle with the data
    it8Handle = cmsIT8LoadFromMem(NULL, data, size);  // Pass NULL for the cmsContext
    if (it8Handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    tableCount = cmsIT8TableCount(it8Handle);

    // Clean up the IT8 handle
    cmsIT8Free(it8Handle);

    return 0;
}