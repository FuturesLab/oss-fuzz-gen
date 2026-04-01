#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_468(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsColorSpaceSignature) + sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Extract cmsColorSpaceSignature from the data
    cmsColorSpaceSignature colorSpaceSignature;
    memcpy(&colorSpaceSignature, data, sizeof(cmsColorSpaceSignature));

    // Extract cmsFloat64Number from the data
    cmsFloat64Number inkLimit;
    memcpy(&inkLimit, data + sizeof(cmsColorSpaceSignature), sizeof(cmsFloat64Number));

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateInkLimitingDeviceLink(colorSpaceSignature, inkLimit);

    // Clean up if profile was successfully created
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}