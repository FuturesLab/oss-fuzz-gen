#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    unsigned char *jpegBuf = const_cast<unsigned char *>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 0;
    int height = 0;

    // Fuzz the tjDecompressHeader function
    int result = tjDecompressHeader(handle, jpegBuf, jpegSize, &width, &height);

    // Clean up
    tjDestroy(handle);

    return 0;
}