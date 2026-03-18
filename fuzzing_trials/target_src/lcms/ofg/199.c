#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2_plugin.h>
#include <lcms2.h>  // Include the main lcms2 header for function declarations

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    const char *columnName;

    // Ensure size is large enough to create a null-terminated string
    if (size < 1) return 0;

    // Initialize the handle (for fuzzing purposes, we assume a valid handle)
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) return 0;

    // Allocate memory for columnName and ensure it is null-terminated
    columnName = (const char *)malloc(size + 1);
    if (columnName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy((char *)columnName, data, size);
    ((char *)columnName)[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    cmsIT8SetIndexColumn(handle, columnName);

    // Additional operations to increase code coverage
    // For example, setting a value for the column
    if (cmsIT8SetData(handle, columnName, "SampleValue", "SamplePatch") != 0) {
        // Handle error if needed
    }

    // Attempt to retrieve the value to ensure the operation was successful
    const char *retrievedValue = cmsIT8GetData(handle, columnName, "SamplePatch");
    if (retrievedValue != NULL) {
        // Use retrievedValue if needed
    }

    // Clean up
    free((void *)columnName);
    cmsIT8Free(handle);

    return 0;
}