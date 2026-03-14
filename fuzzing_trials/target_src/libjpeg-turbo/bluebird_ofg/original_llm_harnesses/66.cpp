#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);

    // Ensure the handle is not NULL before calling tj3Destroy
    if (handle != NULL) {
        tj3Destroy(handle);
    }

    return 0;
}