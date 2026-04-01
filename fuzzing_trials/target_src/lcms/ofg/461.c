#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_461(const uint8_t *data, size_t size) {
    // Initialize a cmsContext, which is a void pointer in Little CMS
    cmsContext context = (cmsContext)data;

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreate_sRGBProfileTHR(context);

    // If a valid profile is created, close it to avoid memory leaks
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}