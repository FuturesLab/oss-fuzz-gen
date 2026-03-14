#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

// Fuzzing harness for cmsDeleteContext
int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    cmsContext context;

    // Initialize the context with some non-NULL value
    context = cmsCreateContext(NULL, NULL);

    // Call the function-under-test
    cmsDeleteContext(context);

    return 0;
}