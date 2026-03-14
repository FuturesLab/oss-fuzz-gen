#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize a memory context
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a profile from memory using the provided data
    cmsHPROFILE hProfile = cmsOpenProfileFromMemTHR(context, data, size);

    // Check if the profile was created successfully
    if (hProfile != NULL) {
        // Call the function-under-test
        cmsIOHANDLER *ioHandler = cmsGetProfileIOhandler(hProfile);

        // If ioHandler is not NULL, perform any required operations
        if (ioHandler != NULL) {
            // Example operation: Use available API functions to interact with the IO handler
            // Since we cannot access ioHandler->Type directly, we avoid this operation.
            // Instead, we can perform other operations allowed by the API.
        }

        // Close the profile
        cmsCloseProfile(hProfile);
    }

    // Free the memory context
    cmsDeleteContext(context);

    return 0;
}