#include <stdint.h>
#include <lcms2.h>

// Fuzzing harness for cmsSetHeaderRenderingIntent
int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number renderingIntent;

    // Ensure the data size is sufficient to extract a rendering intent
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize the renderingIntent from the input data
    renderingIntent = *((cmsUInt32Number *)data);

    // Create a dummy profile for testing
    hProfile = cmsCreate_sRGBProfile();
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsSetHeaderRenderingIntent(hProfile, renderingIntent);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}