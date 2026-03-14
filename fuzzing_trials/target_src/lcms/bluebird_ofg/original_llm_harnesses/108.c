#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to extract a cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize variables
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsUInt32Number channels = *(cmsUInt32Number *)data;

    // Call the function-under-test
    cmsStage *stage = cmsStageAllocIdentity(context, channels);

    // Clean up
    if (stage != NULL) {
        cmsStageFree(stage);
    }

    cmsDeleteContext(context);

    return 0;
}