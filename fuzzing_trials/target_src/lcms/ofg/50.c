#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    cmsHPROFILE hProfile;
    cmsInfoType infoType;
    const char *languageCode = "en";
    const char *countryCode = "US";
    wchar_t buffer[256];
    cmsUInt32Number bufferSize = sizeof(buffer) / sizeof(buffer[0]);

    // Ensure the data size is sufficient for our needs
    if (size < sizeof(cmsHPROFILE) + sizeof(cmsInfoType)) {
        return 0;
    }

    // Extract cmsHPROFILE and cmsInfoType from the input data
    hProfile = *(cmsHPROFILE *)data;
    infoType = *(cmsInfoType *)(data + sizeof(cmsHPROFILE));

    // Call the function-under-test
    cmsUInt32Number result = cmsGetProfileInfo(hProfile, infoType, languageCode, countryCode, buffer, bufferSize);

    // Return 0 to indicate successful execution
    return 0;
}