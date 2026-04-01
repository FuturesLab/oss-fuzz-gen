#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure there is enough data to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateProfilePlaceholder(context);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }
    cmsDeleteContext(context);

    return 0;
}