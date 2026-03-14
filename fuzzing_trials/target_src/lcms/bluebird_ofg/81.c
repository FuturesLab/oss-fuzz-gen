#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "lcms2.h" // Assuming this is the correct header for cmsIT8SetTableByLabel

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a minimum size
    if (size < 3) return 0; // Adjusted to ensure enough data for meaningful input

    // Initialize the parameters for the function-under-test using fuzzer input
    cmsHANDLE handle;
    const char *tabName = (const char *)data; // Use part of the data as tabName
    const char *label = (const char *)(data + 1); // Use another part as label
    const char *value = (const char *)(data + 2); // Use another part as value

    // Create a dummy handle for testing
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) return 0;

    // Call the function-under-test
    int result = cmsIT8SetTableByLabel(handle, tabName, label, value);

    // Clean up the dummy handle
    cmsIT8Free(handle);

    return 0;
}