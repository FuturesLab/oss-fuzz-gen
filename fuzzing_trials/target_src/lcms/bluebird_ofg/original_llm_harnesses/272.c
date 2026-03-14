#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid context and profile
    if (size < sizeof(cmsContext)) {
        return 0;
    }

    // Use a portion of the data to create a context
    cmsContext context = (cmsContext)(uintptr_t)data; // Cast data to cmsContext type

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateNULLProfileTHR(context);

    // Check if the profile is not NULL and perform any additional operations if needed
    if (profile != NULL) {
        // For example, we can close the profile to clean up
        cmsCloseProfile(profile);
    }

    return 0;
}