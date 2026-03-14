#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number Intent;
    cmsBool BPC;

    // Check if the size is sufficient to extract required values
    if (size < sizeof(cmsUInt32Number) + sizeof(cmsBool)) {
        return 0;
    }

    // Create a profile from the data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract Intent and BPC from the data
    Intent = *(cmsUInt32Number *)(data);
    BPC = *(cmsBool *)(data + sizeof(cmsUInt32Number));

    // Call the function-under-test
    cmsUInt32Number result = cmsFormatterForColorspaceOfProfile(hProfile, Intent, BPC);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}