#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number renderingIntent;

    // Ensure the data is large enough to simulate a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Simulate opening a profile using the data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    renderingIntent = cmsGetHeaderRenderingIntent(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}