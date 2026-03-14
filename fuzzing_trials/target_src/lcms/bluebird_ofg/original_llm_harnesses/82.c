#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

// Function signature for the fuzzer entry point
int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Extract a cmsUInt32Number from the input data
    cmsUInt32Number options = *(const cmsUInt32Number *)data;

    // Create a dummy cmsHANDLE
    cmsHPROFILE handle = cmsOpenProfileFromMem(data, size);
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsGDBCompute(handle, options);

    // Clean up
    cmsCloseProfile(handle);

    return 0;
}