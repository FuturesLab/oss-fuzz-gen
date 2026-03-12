#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_423(const uint8_t *data, size_t size) {
    cmsHANDLE handle;
    char *comment;
    cmsBool result;

    // Ensure the input size is sufficient for meaningful operations
    if (size < 1) {
        return 0;
    }

    // Initialize a handle using cmsIT8Alloc, which is a typical way to obtain a cmsHANDLE
    handle = cmsIT8Alloc(NULL);
    if (handle == NULL) {
        return 0; // If allocation fails, exit early
    }

    // Attempt to load the input data into the handle to ensure it's initialized
    if (!cmsIT8LoadFromMem(handle, data, size)) {
        cmsIT8Free(handle);
        return 0; // If loading fails, exit early
    }

    // Allocate memory for the comment and ensure it's null-terminated
    comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        cmsIT8Free(handle);
        return 0; // If allocation fails, exit early
    }
    memcpy(comment, data, size);
    comment[size] = '\0'; // Null-terminate the string

    // Ensure the comment is non-empty to potentially trigger more code paths
    if (size > 0) {
        // Call the function-under-test
        result = cmsIT8SetComment(handle, comment);
        // Check the result of cmsIT8SetComment to avoid further issues
        if (!result) {
            free(comment);
            cmsIT8Free(handle);
            return 0; // If setting the comment fails, exit early
        }
    }

    // Clean up
    free(comment);
    cmsIT8Free(handle);

    return 0;
}