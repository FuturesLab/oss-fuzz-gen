#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    cmsHPROFILE profile;
    cmsFloat64Number version;

    // Initialize the cmsHPROFILE
    profile = cmsCreate_sRGBProfile();
    if (profile == NULL) {
        return 0; // Return if profile creation fails
    }

    // Ensure the data is large enough to extract a double value
    if (size < sizeof(cmsFloat64Number)) {
        cmsCloseProfile(profile);
        return 0;
    }

    // Extract a cmsFloat64Number from the input data
    version = *((cmsFloat64Number*)data);

    // Call the function-under-test
    cmsSetProfileVersion(profile, version);

    // Clean up
    cmsCloseProfile(profile);

    return 0;
}