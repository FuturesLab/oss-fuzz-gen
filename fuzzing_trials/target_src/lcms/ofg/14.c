#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    cmsUInt32Number intent;
    cmsUInt32Number flags;

    // Ensure there is enough data to initialize variables
    if (size < sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    // Initialize variables using the input data
    intent = *((cmsUInt32Number *)data);
    flags = *((cmsUInt32Number *)(data + sizeof(cmsUInt32Number)));

    // Open a dummy profile for testing
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIsIntentSupported(hProfile, intent, flags);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}