#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    unsigned long bufferSize = tjBufSize(width, height, jpegSubsamp);
    unsigned char *buffer = static_cast<unsigned char *>(malloc(bufferSize));
    if (buffer == nullptr) {
        tjDestroy(handle);
        return 0;
    }

    if (tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT) != 0) {
        free(buffer);
        tjDestroy(handle);
        return 0;
    }

    free(buffer);
    tjDestroy(handle);

    return 0;
}