#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2.h"

static cmsHANDLE createDummyIT8Handle() {
    // Normally, you would create a valid IT8 handle here.
    // For fuzzing, we simulate with a more realistic dummy handle.
    // Allocate enough memory to simulate a valid IT8 structure.
    return cmsIT8Alloc(NULL);
}

static void destroyDummyIT8Handle(cmsHANDLE hIT8) {
    if (hIT8) {
        cmsIT8Free(hIT8);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cmsHANDLE hIT8 = createDummyIT8Handle();
    if (!hIT8) {
        return 0;
    }

    // Creating strings from input data
    char cProp[256], cPatch[256], cSample[256];
    cmsFloat64Number Val = 0.0;

    // Limit the size for strings
    size_t propSize = Size > 255 ? 255 : Size;
    size_t patchSize = Size > 255 ? 255 : Size;
    size_t sampleSize = Size > 255 ? 255 : Size;

    strncpy(cProp, (const char*)Data, propSize);
    cProp[propSize] = '\0';

    strncpy(cPatch, (const char*)Data, patchSize);
    cPatch[patchSize] = '\0';

    strncpy(cSample, (const char*)Data, sampleSize);
    cSample[sampleSize] = '\0';

    // Convert some bytes to a double value
    if (Size >= sizeof(cmsFloat64Number)) {
        memcpy(&Val, Data, sizeof(cmsFloat64Number));
    }

    // Invoke target functions with fuzzed input
    const char* propVal = cmsIT8GetProperty(hIT8, cProp);
    cmsBool setDataResult = cmsIT8SetDataDbl(hIT8, cPatch, cSample, Val);
    cmsBool setPropResult = cmsIT8SetPropertyDbl(hIT8, cProp, Val);
    cmsFloat64Number getPropDblVal = cmsIT8GetPropertyDbl(hIT8, cProp);
    cmsFloat64Number getDataDblVal = cmsIT8GetDataDbl(hIT8, cPatch, cSample);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cmsIT8GetData with cmsIT8GetPropertyMulti
    const char* dataVal = cmsIT8GetPropertyMulti(hIT8, cPatch, cSample);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Handle the results if needed (e.g., check for NULL or errors)
    if (propVal) {
        // Do something with propVal
    }

    if (dataVal) {
        // Do something with dataVal
    }

    // Cleanup
    destroyDummyIT8Handle(hIT8);

    return 0;
}