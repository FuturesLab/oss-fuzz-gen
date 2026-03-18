#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_488(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for cmsMLUalloc
    cmsContext context = (cmsContext)(uintptr_t)data; // Cast data to cmsContext
    cmsUInt32Number num = (cmsUInt32Number)(size > 0 ? data[0] : 1); // Use first byte of data or default to 1

    // Call the function-under-test
    cmsMLU *mlu = cmsMLUalloc(context, num);

    // Clean up
    if (mlu != NULL) {
        cmsMLUfree(mlu);
    }

    return 0;
}