#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);

    // Close the profile
    cmsCloseProfile(hProfile);

    return 0;
}