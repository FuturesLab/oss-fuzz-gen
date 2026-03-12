#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Call the function-under-test
    cmsHPROFILE profile = cmsOpenProfileFromMem(data, size);

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Perform operations on the profile if needed
        // For this fuzzing harness, we'll just close the profile
        cmsCloseProfile(profile);
    }

    return 0;
}