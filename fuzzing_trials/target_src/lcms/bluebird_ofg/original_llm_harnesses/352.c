#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    cmsUInt32Number tableIndex;

    // Ensure the data size is sufficient for our needs
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize handle using cmsIT8Alloc, assuming a valid context
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Extract tableIndex from the input data
    tableIndex = *(cmsUInt32Number *)data;

    // Call the function under test
    cmsInt32Number result = cmsIT8SetTable(handle, tableIndex);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}