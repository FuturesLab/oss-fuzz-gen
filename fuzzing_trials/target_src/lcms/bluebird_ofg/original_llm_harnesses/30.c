#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    cmsStage *stage = NULL;

    // Initialize the stage with a non-NULL value
    if (size > 0) {
        stage = cmsStageAllocIdentity(NULL, size);
    }

    // Ensure stage is not NULL before calling the function-under-test
    if (stage != NULL) {
        cmsStageFree(stage);
    }

    return 0;
}