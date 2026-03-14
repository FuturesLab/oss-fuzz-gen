#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context = NULL;
    cmsHPROFILE profile = NULL;

    // Check if the input size is sufficient for our needs
    if (size < sizeof(cmsContext)) {
        return 0;
    }

    // Create a context from the input data
    // For the purpose of this example, we assume the context is an integer
    // and we use the first bytes of data to set it.
    context = (cmsContext)(*((int*)data));

    // Call the function-under-test
    profile = cmsCreate_OkLabProfile(context);

    // Clean up
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}