extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    tjhandle handle = nullptr;
    tjtransform transform;
    size_t bufferSize = 0;

    // Initialize the transform structure with some default values
    memset(&transform, 0, sizeof(tjtransform));

    // Create a TurboJPEG decompressor or compressor handle
    handle = tjInitTransform();
    if (handle == nullptr) {
        return 0;
    }

    // Call the function under test
    bufferSize = tj3TransformBufSize(handle, &transform);

    // Clean up the TurboJPEG handle
    tjDestroy(handle);

    return 0;
}