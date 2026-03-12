#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>
#include <string.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    if (size < sizeof(cmsUInt32Number) * 2 + sizeof(cmsFloat64Number) * 4) {
        // Not enough data to extract all parameters
        return 0;
    }

    // Extract parameters from the input data
    cmsUInt32Number nChannels = data[0] % 10 + 1; // Ensure nChannels is between 1 and 10
    cmsFloat64Number L = *((cmsFloat64Number*)(data + 1));
    L = fmod(L, 100.0); // L* between 0 and 100 using fmod
    cmsFloat64Number a = *((cmsFloat64Number*)(data + 1 + sizeof(cmsFloat64Number)));
    cmsFloat64Number b = *((cmsFloat64Number*)(data + 1 + 2 * sizeof(cmsFloat64Number)));
    cmsFloat64Number c = *((cmsFloat64Number*)(data + 1 + 3 * sizeof(cmsFloat64Number)));
    cmsUInt32Number intent = data[1 + 4 * sizeof(cmsFloat64Number)] % 4; // Intent between 0 and 3
    cmsUInt32Number flags = data[2 + 4 * sizeof(cmsFloat64Number)]; // Use as flags

    // Call the function-under-test
    cmsHPROFILE profile = cmsCreateBCHSWabstractProfile(nChannels, L, a, b, c, intent, flags);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Do something with the profile, if necessary
        cmsCloseProfile(profile);
    }

    return 0;
}