#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the string.h library for memcpy
#include <lcms2.h>

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0; // Exit if context creation fails
    }

    // Ensure that the input size is sufficient for the function under test
    if (size < sizeof(cmsCIExyYTRIPLE)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Use the input data to create a cmsCIExyYTRIPLE structure
    cmsCIExyYTRIPLE triple;
    memcpy(&triple, data, sizeof(cmsCIExyYTRIPLE));

    // Call the function-under-test with the created structure
    cmsHPROFILE profile = cmsCreate_OkLabProfile(context);
    
    // Check if profile creation was successful
    if (profile != NULL) {
        // Do something with the profile if needed
        // For fuzzing, we might not need to do anything specific

        // Release the profile after use
        cmsCloseProfile(profile);
    }

    // Delete the context after use
    cmsDeleteContext(context);

    return 0;
}