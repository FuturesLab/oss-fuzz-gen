#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    unsigned long jpegSize = (unsigned long)size;
    int width = 0;
    int height = 0;

    // Call the function-under-test
    tjDecompressHeader(handle, (unsigned char *)data, jpegSize, &width, &height);

    tjDestroy(handle);
    return 0;
}