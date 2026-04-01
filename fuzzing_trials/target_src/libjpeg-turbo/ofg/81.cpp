#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Not enough data to form a valid JPEG header
    }

    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (buffer != NULL) {
            tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }

    // Clean up
    tjDestroy(handle);

    return 0;
}