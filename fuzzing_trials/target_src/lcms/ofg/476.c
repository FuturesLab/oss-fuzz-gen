#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_476(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsHPROFILE hProfile;
    struct tm creationDateTime;

    // Ensure size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a profile from the input data
    hProfile = cmsOpenProfileFromMem((void*)data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsGetHeaderCreationDateTime(hProfile, &creationDateTime);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}