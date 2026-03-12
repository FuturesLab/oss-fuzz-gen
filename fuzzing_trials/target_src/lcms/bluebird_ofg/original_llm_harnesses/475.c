#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_475(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    struct tm creationDateTime;

    // Ensure the data is not empty
    if (size == 0) {
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