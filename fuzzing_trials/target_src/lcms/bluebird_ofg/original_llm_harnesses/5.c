#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure we have enough data to initialize cmsCIExyY
    if (size < sizeof(cmsCIExyY)) {
        return 0;
    }

    // Cast the input data to cmsCIExyY
    cmsCIExyY *xyY = (cmsCIExyY *)data;

    // Create a Lab2 profile using the input data
    cmsHPROFILE profile = cmsCreateLab2Profile(xyY);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Do something with the profile, if needed
        // ...

        // Release the profile after use
        cmsCloseProfile(profile);
    }

    return 0;
}