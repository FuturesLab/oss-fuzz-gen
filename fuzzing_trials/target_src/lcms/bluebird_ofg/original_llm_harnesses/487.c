#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Fuzzing harness for cmsMLUalloc function
int LLVMFuzzerTestOneInput_487(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsContext context = (cmsContext)0x1;  // Non-NULL context
    cmsUInt32Number num = 1;               // Non-zero number

    // Call the function-under-test
    cmsMLU *mlu = cmsMLUalloc(context, num);

    // Clean up if allocation was successful
    if (mlu != NULL) {
        cmsMLUfree(mlu);
    }

    return 0;
}