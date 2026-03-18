#include <stdint.h>
#include <stdlib.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the cmsContext and void* pointer
    if (size < sizeof(cmsContext) + sizeof(void*)) {
        return 0;
    }

    // Extract cmsContext from the input data
    cmsContext context = *(cmsContext*)(data);

    // Extract a pointer from the input data
    void* ptr = (void*)(data + sizeof(cmsContext));

    // Call the function under test
    cmsBool result = cmsPluginTHR(context, ptr);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if needed
    }

    return 0;
}