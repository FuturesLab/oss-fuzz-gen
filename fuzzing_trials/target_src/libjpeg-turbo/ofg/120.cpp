#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to process
    }

    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Failed to initialize decompressor
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        unsigned long bufferSize = tjBufSize(width, height, jpegSubsamp);
        unsigned char *buffer = new unsigned char[bufferSize];

        if (buffer != NULL) {
            if (tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT) == 0) {
                // Successfully decompressed image
            }
            delete[] buffer;
        }
    }

    tjDestroy(handle);
    return 0;
}