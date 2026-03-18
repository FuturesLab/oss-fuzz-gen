#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a valid profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Create a memory profile from the input data
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    if (hProfile == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsFloat64Number tac = cmsDetectTAC(hProfile);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}