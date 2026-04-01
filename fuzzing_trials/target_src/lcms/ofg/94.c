#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

typedef cmsBool (*cmsSAMPLER16)(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo);

cmsBool SampleFunction(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    // A simple sampler function that just copies input to output.
    for (int i = 0; i < 3; i++) {
        Out[i] = In[i];
    }
    return TRUE;
}

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Ensure there's enough data for at least one cmsUInt32Number
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize parameters for cmsSliceSpace16
    cmsUInt32Number nInputs = *(const cmsUInt32Number*)data;
    data += sizeof(cmsUInt32Number);
    size -= sizeof(cmsUInt32Number);

    // Ensure there's enough data for nInputs cmsUInt32Number values
    if (size < nInputs * sizeof(cmsUInt32Number)) {
        return 0;
    }

    const cmsUInt32Number *clutPoints = (const cmsUInt32Number*)data;
    cmsSAMPLER16 Sampler = SampleFunction;
    void *Cargo = NULL; // No additional data needed for this simple sampler

    // Call the function-under-test
    cmsBool result = cmsSliceSpace16(nInputs, clutPoints, Sampler, Cargo);

    (void)result; // Silence unused variable warning

    return 0;
}