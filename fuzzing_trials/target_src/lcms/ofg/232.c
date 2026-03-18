#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a cmsStage object
    // Since cmsStage is an incomplete type, we cannot use sizeof(cmsStage).
    // Instead, we determine a reasonable size to proceed with fuzzing.
    if (size < 3 * sizeof(double)) {
        return 0;
    }

    // Allocating an identity stage
    cmsStage *stage = cmsStageAllocIdentity(NULL, 3);

    if (stage == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsContext contextID = cmsGetStageContextID(stage);

    // Use the contextID in some way to avoid compiler optimizations
    if (contextID != NULL) {
        // Dummy operation to use contextID
        (void)contextID;
    }

    // Free the allocated stage
    cmsStageFree(stage);

    return 0;
}