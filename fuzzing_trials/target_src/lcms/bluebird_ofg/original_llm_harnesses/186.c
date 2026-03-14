#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    const char *varName = "SampleVar";
    const char *subscript = "SampleSub";
    cmsFloat64Number value = 123.456;

    // Initialize a dummy handle for testing purposes
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Ensure the data is not NULL, and use it to modify the value
    if (size >= sizeof(cmsFloat64Number)) {
        memcpy(&value, data, sizeof(cmsFloat64Number));
    }

    // Call the function-under-test
    cmsBool result = cmsIT8SetDataDbl(handle, varName, subscript, value);

    // Clean up
    cmsIT8Free(handle);

    return 0;
}