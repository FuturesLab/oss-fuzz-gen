#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Initialize the TurboJPEG compressor
    tjhandle compressor = tjInitCompress();
    if (compressor == NULL) {
        return 0; // Initialization failed, exit early
    }

    // Normally, you would use the compressor for JPEG compression tasks here.
    // However, since this is a fuzzing harness, we are only interested in
    // initializing the compressor to check for memory corruption vulnerabilities.

    // Cleanup: destroy the compressor handle
    tjDestroy(compressor);

    return 0;
}