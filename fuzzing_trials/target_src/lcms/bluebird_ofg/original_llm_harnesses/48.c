#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile using the provided data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsUInt32Number model = cmsGetHeaderModel(hProfile);

    // Clean up and close the profile
    cmsCloseProfile(hProfile);

    return 0;
}