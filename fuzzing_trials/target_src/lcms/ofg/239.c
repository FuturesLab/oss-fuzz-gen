#include <stdint.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to fill a cmsCIExyY structure
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Initialize a cmsCIExyY structure from the input data
    cmsCIExyY whitePoint;
    memcpy(&whitePoint, data, sizeof(cmsCIExyY));

    // Create a Lab4 profile using the initialized cmsCIExyY structure
    cmsHPROFILE profile = cmsCreateLab4Profile(&whitePoint);

    // If the profile was created successfully, release it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}