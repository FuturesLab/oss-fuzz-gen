#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <lcms2.h>

int LLVMFuzzerTestOneInput_491(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to cast to cmsContext
    if (size < sizeof(cmsContext)) {
        return 0; // Not enough data to proceed
    }

    // Declare and initialize variables for the function parameters
    cmsContext context = (cmsContext)data; // Cast data to cmsContext
    cmsUInt32Number flags = 0; // Initialize flags to 0
    cmsFloat64Number brightness = 1.0; // Initialize brightness to a non-zero value
    cmsFloat64Number contrast = 1.0; // Initialize contrast to a non-zero value
    cmsFloat64Number hue = 1.0; // Initialize hue to a non-zero value
    cmsFloat64Number saturation = 1.0; // Initialize saturation to a non-zero value
    cmsUInt32Number intent = 0; // Initialize intent to 0
    cmsUInt32Number space = 0; // Initialize space to 0

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateBCHSWabstractProfileTHR(context, flags, brightness, contrast, hue, saturation, intent, space);

    // If the profile is created, close it to avoid memory leaks
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}