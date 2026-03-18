#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;
    cmsInfoType infoType = cmsInfoDescription;
    const char *languageCode = "en";
    const char *countryCode = "US";
    char buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer);

    // Ensure the data is not empty and fits within a reasonable size for a profile
    if (size > 0 && size <= 1024) {
        // Create a memory profile from the input data
        hProfile = cmsOpenProfileFromMem(data, size);

        if (hProfile != NULL) {
            // Call the function-under-test
            cmsUInt32Number result = cmsGetProfileInfoASCII(hProfile, infoType, languageCode, countryCode, buffer, bufferSize);

            // Close the profile after use
            cmsCloseProfile(hProfile);
        }
    }

    return 0;
}