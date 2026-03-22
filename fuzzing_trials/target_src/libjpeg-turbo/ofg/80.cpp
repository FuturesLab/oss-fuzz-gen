#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Initialize a tjhandle for fuzzing
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // If initialization fails, exit early
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        unsigned char *buffer = new unsigned char[width * height * tjPixelSize[TJPF_RGB]];

        if (tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT) == 0) {
            // Successfully decompressed, use buffer in some way
        }

        delete[] buffer;
    }

    // Clean up the tjhandle
    tjDestroy(handle);

    return 0;
}