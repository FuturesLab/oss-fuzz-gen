#include <cstddef>
#include <cstdint>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    int width = 0;
    int height = 0;
    int jpegSubsamp = 0;
    int jpegColorspace = 0;

    if (size > 0) {
        tjDecompressHeader3(handle, data, static_cast<unsigned long>(size), &width, &height, &jpegSubsamp, &jpegColorspace);
    }

    tjDestroy(handle);
    return 0;
}