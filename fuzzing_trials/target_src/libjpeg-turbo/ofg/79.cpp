#include <cstdint>
#include <cstdlib>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    unsigned char *jpegBuf = const_cast<unsigned char*>(data);
    unsigned long jpegSize = static_cast<unsigned long>(size);
    int width = 0, height = 0, jpegSubsamp = 0;

    // Call the function-under-test
    tjDecompressHeader2(handle, jpegBuf, jpegSize, &width, &height, &jpegSubsamp);

    tjDestroy(handle);
    return 0;
}