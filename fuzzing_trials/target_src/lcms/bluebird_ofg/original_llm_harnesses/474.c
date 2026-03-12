#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_474(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateXYZProfileTHR(context);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}