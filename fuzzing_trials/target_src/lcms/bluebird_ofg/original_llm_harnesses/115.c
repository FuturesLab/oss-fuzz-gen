#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsHPROFILE hProfile;
    cmsInfoType infoType;
    const char* languageCode = "en";
    const char* countryCode = "US";
    char buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer);

    // Create a dummy profile for testing
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0; // Exit if the profile cannot be opened
    }

    // Iterate over possible infoType values for fuzzing
    for (infoType = cmsInfoDescription; infoType <= cmsInfoCopyright; infoType = (cmsInfoType)((int)infoType + 1)) {
        // Call the function-under-test
        cmsGetProfileInfoASCII(hProfile, infoType, languageCode, countryCode, buffer, bufferSize);
    }

    // Close the profile after testing
    cmsCloseProfile(hProfile);

    return 0;
}