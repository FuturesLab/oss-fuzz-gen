#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *propertyName;
    cmsFloat64Number result;

    // Ensure size is large enough to extract a property name
    if (size < 1) {
        return 0;
    }

    // Initialize a dummy handle for testing
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0;
    }

    // Allocate memory for the property name and ensure it's null-terminated
    propertyName = (char *)malloc(size + 1);
    if (propertyName == NULL) {
        cmsIT8Free(handle);
        return 0;
    }
    memcpy(propertyName, data, size);
    propertyName[size] = '\0';  // Null-terminate the string

    // Set a dummy property to ensure the property name is valid
    cmsIT8SetPropertyDbl(handle, "DUMMY_PROPERTY", 1.0);

    // Call the function under test
    result = cmsIT8GetPropertyDbl(handle, propertyName);

    // Check result to ensure the function was invoked meaningfully
    if (result != 0.0) {
        // Do something with the result if needed
    }

    // Clean up
    free(propertyName);
    cmsIT8Free(handle);

    return 0;
}