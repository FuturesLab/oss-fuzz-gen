#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Remove 'extern "C"' to make it C compatible
int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsFloat64Number inputNumber;
    cmsFloat64Number result;

    // Initialize cmsHPROFILE with a default profile
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0; // Exit if profile creation fails
    }

    // Ensure the input data is large enough to extract a cmsFloat64Number
    if (size < sizeof(cmsFloat64Number)) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Use the first part of the data as the cmsFloat64Number
    inputNumber = *((cmsFloat64Number *)data);

    // Call the function-under-test
    result = cmsDetectRGBProfileGamma(hProfile, inputNumber);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}