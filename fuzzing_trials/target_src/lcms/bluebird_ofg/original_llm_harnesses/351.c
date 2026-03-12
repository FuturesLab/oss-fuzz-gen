#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    // Initialize the parameters for the function-under-test
    cmsHANDLE handle;
    cmsUInt32Number tableIndex;

    // Ensure that size is large enough to extract the parameters
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize the handle with a non-NULL value
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract tableIndex from the input data
    tableIndex = *(cmsUInt32Number *)data;

    // Call the function-under-test
    cmsInt32Number result = cmsIT8SetTable(handle, tableIndex);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}