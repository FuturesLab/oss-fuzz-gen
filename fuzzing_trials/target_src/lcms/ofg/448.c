#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <lcms2.h>

int LLVMFuzzerTestOneInput_448(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile;
    cmsUInt32Number manufacturer;

    // Check if the input size is sufficient to create a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory-based profile using the input data
    hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function under test
    manufacturer = cmsGetHeaderManufacturer(hProfile);

    // Close the profile after use
    cmsCloseProfile(hProfile);

    return 0;
}