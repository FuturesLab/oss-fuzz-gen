#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsInfoType infoType;
    char language[3] = "en"; // ISO 639-1 code for English
    char country[3] = "US";  // ISO 3166-1 alpha-2 code for United States
    char buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer);

    // Ensure data is large enough to extract necessary information
    if (size < sizeof(cmsInfoType)) {
        return 0;
    }

    // Create a profile from memory using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Extract cmsInfoType from the input data
    memcpy(&infoType, data, sizeof(cmsInfoType));

    // Call the function-under-test
    cmsUInt32Number result = cmsGetProfileInfoUTF8(hProfile, infoType, language, country, buffer, bufferSize);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}