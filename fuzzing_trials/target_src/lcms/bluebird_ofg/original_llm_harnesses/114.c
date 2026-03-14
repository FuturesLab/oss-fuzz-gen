#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Define a sample sampler function
static int MySampler(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    for (int i = 0; i < 3; i++) {
        Out[i] = In[i];
    }
    return 1; // Return 1 to indicate success
}

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Initialize a cmsStage object
    cmsStage *stage = cmsStageAllocCLut16bit(NULL, 3, 3, 3, NULL);
    if (stage == NULL) {
        return 0;
    }

    // Ensure the data size is sufficient for the test
    if (size < sizeof(cmsUInt32Number)) {
        cmsStageFree(stage);
        return 0;
    }

    // Use the first bytes of data as the cmsUInt32Number parameter
    cmsUInt32Number nPoints = *(cmsUInt32Number*)data;

    // Call the function-under-test
    cmsStageSampleCLut16bit(stage, MySampler, NULL, nPoints);

    // Free the cmsStage object
    cmsStageFree(stage);

    return 0;
}