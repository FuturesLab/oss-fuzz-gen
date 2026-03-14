#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_489(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsContext context;
    cmsUInt32Number n = 1; // Set a non-zero value for cmsUInt32Number

    // Ensure that data is not NULL and size is greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a cmsContext using the data
    context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Call the function-under-test
    cmsSEQ *seq = cmsAllocProfileSequenceDescription(context, n);

    // Check if the sequence is allocated successfully
    if (seq != NULL) {
        // Free the allocated sequence
        cmsFreeProfileSequenceDescription(seq);
    }

    // Free the context
    cmsDeleteContext(context);

    return 0;
}