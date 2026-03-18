#include <stdint.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    cmsHPROFILE hProfile = NULL;
    cmsContext contextID;

    // Check if the size is sufficient to simulate a profile
    if (size < sizeof(cmsHPROFILE)) {
        return 0;
    }

    // Simulate creating a profile from the input data
    // In a real scenario, you would use a function like cmsOpenProfileFromMem
    // to create a profile from the data, but here we simulate it for fuzzing purposes
    hProfile = cmsOpenProfileFromMem(data, size);

    // Ensure the profile is not NULL
    if (hProfile != NULL) {
        // Call the function-under-test
        contextID = cmsGetProfileContextID(hProfile);

        // Close the profile to prevent memory leaks
        cmsCloseProfile(hProfile);
    }

    return 0;
}