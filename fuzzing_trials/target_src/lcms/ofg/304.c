#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    cmsContext context = cmsCreateContext(NULL, NULL);
    cmsHANDLE handle = NULL;

    if (size > 0) {
        // Call the function-under-test with the provided data
        handle = cmsIT8LoadFromMem(context, (const void *)data, (cmsUInt32Number)size);
        
        // If handle is not NULL, we should free it to avoid memory leaks
        if (handle != NULL) {
            cmsIT8Free(handle);
        }
    }

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}