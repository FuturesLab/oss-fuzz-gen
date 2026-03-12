#include <stdint.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsInfoType infoType;
    const char *languageCode = "en";
    const char *countryCode = "US";
    char buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer);

    // Ensure the data size is sufficient for creating a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Initialize the profile handle from the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Iterate over possible infoType values
    for (int i = 0; i < 6; i++) {
        infoType = (cmsInfoType)i;

        // Call the function-under-test
        cmsGetProfileInfoUTF8(hProfile, infoType, languageCode, countryCode, buffer, bufferSize);
    }

    // Close the profile handle
    cmsCloseProfile(hProfile);

    return 0;
}