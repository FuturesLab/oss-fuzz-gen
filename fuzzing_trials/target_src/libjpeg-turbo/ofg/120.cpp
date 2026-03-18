#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize variables
    tjhandle handle = tjInitTransform();
    tjtransform transform;
    
    // Ensure handle is not NULL
    if (handle == NULL) {
        return 0;
    }

    // Initialize the transform structure with default values
    transform.op = TJXOP_NONE;  // No transform operation
    transform.options = 0;      // No options
    transform.r.x = 0;          // Region of interest x-coordinate
    transform.r.y = 0;          // Region of interest y-coordinate
    transform.r.w = 0;          // Region of interest width
    transform.r.h = 0;          // Region of interest height
    transform.customFilter = NULL; // No custom filter

    // Call the function-under-test
    size_t bufSize = tj3TransformBufSize(handle, &transform);

    // Clean up
    tjDestroy(handle);

    return 0;
}