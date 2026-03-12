#include <stdint.h>
#include <string.h> // Include for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Declare and initialize the cmsCIExyY structure
    cmsCIExyY whitePoint;
    cmsHPROFILE profile;

    // Ensure that the data size is sufficient to fill the cmsCIExyY structure
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Copy data into the cmsCIExyY structure
    // Note: This is a simple way to initialize the structure with data.
    // In a real-world scenario, you might want to ensure the data is valid for the context.
    memcpy(&whitePoint, data, sizeof(cmsCIExyY));

    // Call the function-under-test
    profile = cmsCreateLab4Profile(&whitePoint);

    // Clean up: Check if the profile was created and free it
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}