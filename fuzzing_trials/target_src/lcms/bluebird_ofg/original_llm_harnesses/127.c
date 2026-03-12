#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < sizeof(cmsCIEXYZ) + 2 * sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize the parameters
    cmsCIEXYZ blackPoint;
    cmsHPROFILE hProfile;
    cmsUInt32Number intent, flags;

    // Extract data for cmsCIEXYZ
    memcpy(&blackPoint, data, sizeof(cmsCIEXYZ));
    data += sizeof(cmsCIEXYZ);
    size -= sizeof(cmsCIEXYZ);

    // Extract data for cmsUInt32Number intent
    memcpy(&intent, data, sizeof(cmsUInt32Number));
    data += sizeof(cmsUInt32Number);
    size -= sizeof(cmsUInt32Number);

    // Extract data for cmsUInt32Number flags
    memcpy(&flags, data, sizeof(cmsUInt32Number));
    data += sizeof(cmsUInt32Number);
    size -= sizeof(cmsUInt32Number);

    // Create a dummy profile for fuzzing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsDetectBlackPoint(&blackPoint, hProfile, intent, flags);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}