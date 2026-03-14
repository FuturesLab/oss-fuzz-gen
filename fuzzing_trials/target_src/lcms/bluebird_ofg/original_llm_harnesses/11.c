#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Create a profile using the data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract a cmsUInt32Number from the data
    cmsUInt32Number renderingIntent = *(const cmsUInt32Number*)data;

    // Call the function-under-test
    cmsSetHeaderRenderingIntent(hProfile, renderingIntent);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}