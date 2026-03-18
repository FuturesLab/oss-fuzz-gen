#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsColorSpaceSignature colorSpace;
    cmsFloat64Number limit;

    // Ensure the size is sufficient to extract necessary data
    if (size < sizeof(cmsColorSpaceSignature) + sizeof(cmsFloat64Number)) {
        return 0;
    }

    // Extract colorSpace and limit from the input data
    colorSpace = *(cmsColorSpaceSignature*)data;
    limit = *(cmsFloat64Number*)(data + sizeof(cmsColorSpaceSignature));

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateInkLimitingDeviceLinkTHR(context, colorSpace, limit);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}