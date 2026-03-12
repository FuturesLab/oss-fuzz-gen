#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize the parameters for the function
    cmsHPROFILE hProfile = cmsOpenProfileFromMem(data, size);
    cmsUInt32Number version;

    // Extract cmsUInt32Number from the input data
    version = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    if (hProfile != NULL) {
        cmsSetEncodedICCversion(hProfile, version);

        // Clean up
        cmsCloseProfile(hProfile);
    }

    return 0;
}