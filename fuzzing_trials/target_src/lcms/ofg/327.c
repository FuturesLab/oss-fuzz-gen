#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_327(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract parameters
    if (size < sizeof(cmsUInt32Number) + sizeof(cmsBool)) {
        return 0;
    }

    // Initialize variables
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    cmsUInt32Number format = *(const cmsUInt32Number *)(data);
    cmsBool isInput = *(const cmsBool *)(data + sizeof(cmsUInt32Number));

    // Call the function-under-test
    cmsUInt32Number result = cmsFormatterForPCSOfProfile(hProfile, format, isInput);

    // Close the profile if it was successfully opened
    cmsCloseProfile(hProfile);

    return 0;
}