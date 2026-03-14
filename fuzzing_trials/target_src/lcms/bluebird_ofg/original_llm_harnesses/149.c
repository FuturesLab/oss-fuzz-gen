#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);

    // Clean up the profile if it was successfully created
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}