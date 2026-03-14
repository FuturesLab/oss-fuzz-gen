#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_417(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a profile
    if (size < sizeof(cmsCIExyYTRIPLE) + sizeof(cmsCIExyY)) {
        return 0; // Not enough data to proceed
    }

    // Use the input data to create a custom RGB profile
    cmsCIExyYTRIPLE primaries;
    cmsCIExyY whitePoint;

    // Copy data into primaries and whitePoint
    memcpy(&primaries, data, sizeof(cmsCIExyYTRIPLE));
    memcpy(&whitePoint, data + sizeof(cmsCIExyYTRIPLE), sizeof(cmsCIExyY));

    cmsToneCurve* gamma[3] = { cmsBuildGamma(NULL, 2.2), cmsBuildGamma(NULL, 2.2), cmsBuildGamma(NULL, 2.2) };
    cmsHPROFILE profile = cmsCreateRGBProfile(&whitePoint, &primaries, gamma);

    // Release the tone curves
    cmsFreeToneCurve(gamma[0]);
    cmsFreeToneCurve(gamma[1]);
    cmsFreeToneCurve(gamma[2]);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Perform operations on the profile if needed

        // Finally, release the profile to avoid memory leaks
        cmsCloseProfile(profile);
    }

    return 0;
}