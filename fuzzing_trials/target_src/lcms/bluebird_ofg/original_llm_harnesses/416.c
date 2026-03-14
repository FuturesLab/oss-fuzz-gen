#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_416(const uint8_t *data, size_t size) {
    // Call the function-under-test
    cmsHPROFILE profile = cmsCreate_sRGBProfile();

    // Check if the profile was created successfully
    if (profile != NULL) {
        // Use the input data to modify the profile if possible
        if (size > 0) {
            // Example: use the first byte of data to set a profile attribute
            // This is a placeholder for actual logic that uses the input data
            cmsSetProfileVersion(profile, data[0] / 255.0 * 4.0 + 2.0); // Version between 2.0 and 6.0
        }

        // Do something with the profile, such as closing it
        cmsCloseProfile(profile);
    }

    // Return 0 to indicate successful execution
    return 0;
}