#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitTransform();
    if (!handle) {
        return 0;
    }

    // Ensure the input size is reasonable
    if (size < 1) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for the transformed image
    unsigned char *jpegBuf = NULL;
    size_t jpegSize = 0;

    // Define a transformation
    tjtransform transform;
    memset(&transform, 0, sizeof(tjtransform));
    transform.op = TJXOP_NONE;  // No transformation

    // Call the function under test
    int result = tj3Transform(handle, data, size, 0, &jpegBuf, &jpegSize, &transform);

    // Clean up
    if (jpegBuf != NULL) {
        tjFree(jpegBuf);
    }
    tjDestroy(handle);

    return result;
}