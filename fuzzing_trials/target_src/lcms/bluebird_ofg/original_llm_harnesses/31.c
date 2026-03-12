#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a cmsContext
    if (size < sizeof(void*)) {
        return 0;
    }

    // Create a dummy user data
    void *userData = (void *)(uintptr_t)(data[0]);

    // Create a cmsContext with the dummy user data
    cmsContext context = cmsCreateContext(NULL, userData);

    // Call the function-under-test
    void *retrievedUserData = cmsGetContextUserData(context);

    // Optionally, you can add some checks or assertions here
    if (retrievedUserData != userData) {
        // Handle the case where the retrieved user data does not match
    }

    // Clean up
    cmsDeleteContext(context);

    return 0;
}