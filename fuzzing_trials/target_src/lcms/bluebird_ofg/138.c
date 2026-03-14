#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include string.h for memcpy
#include "lcms2.h"

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to fill the cmsViewingConditions structure
    if (size < sizeof(cmsViewingConditions)) {
        return 0;
    }

    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Create a cmsViewingConditions object and fill it with data
    cmsViewingConditions viewingConditions;
    memcpy(&viewingConditions, data, sizeof(cmsViewingConditions));

    // Call the function-under-test
    cmsHANDLE handle = cmsCIECAM02Init(context, &viewingConditions);

    // Cleanup
    if (handle != NULL) {
        cmsCIECAM02Done(handle);
    }

    cmsDeleteContext(context);

    return 0;
}