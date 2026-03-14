#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

// Fuzzing harness for cmsIT8SetDataDbl
int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsHANDLE handle = cmsIT8Alloc(NULL);
    const char *varName = "SampleVariable";
    const char *subVarName = "SampleSubVariable";
    cmsFloat64Number value = 1.23;

    // Ensure the handle is not NULL
    if (handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataDbl(handle, varName, subVarName, value);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}