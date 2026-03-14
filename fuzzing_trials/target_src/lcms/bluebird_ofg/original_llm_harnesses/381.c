#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_381(const uint8_t *data, size_t size) {
    cmsHPROFILE profile;
    const char *filename = "output.icc";

    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a dummy profile for fuzzing purposes
    profile = cmsCreate_sRGBProfile();
    if (profile == NULL) {
        return 0;
    }

    // Attempt to save the profile to a file
    cmsBool result = cmsSaveProfileToFile(profile, filename);

    // Clean up
    cmsCloseProfile(profile);

    return 0;
}