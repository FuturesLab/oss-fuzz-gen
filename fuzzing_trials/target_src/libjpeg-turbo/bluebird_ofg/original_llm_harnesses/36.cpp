#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    unsigned char *jpegBuf = (unsigned char *)data;
    unsigned long jpegSize = (unsigned long)size;
    int width = 0, height = 0, jpegSubsamp = 0;

    // Call the function-under-test
    int result = tjDecompressHeader2(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp);

    // Clean up
    tjDestroy(handle);

    return 0;
}