#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_490(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    // Initialize a cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Extract a cmsUInt32Number from the input data
    cmsUInt32Number num = *(const cmsUInt32Number *)data;

    // Call the function-under-test
    cmsSEQ *seq = cmsAllocProfileSequenceDescription(context, num);

    // Clean up
    if (seq != NULL) {
        cmsFreeProfileSequenceDescription(seq);
    }
    cmsDeleteContext(context);

    return 0;
}