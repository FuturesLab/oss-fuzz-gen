#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to be a valid JPEG header
    }

    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (buffer != nullptr) {
            // Attempt to decompress the image
            int pitch = width * tjPixelSize[TJPF_RGB];
            tjDecompress2(handle, data, size, buffer, width, pitch, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }

    tjDestroy(handle);
    return 0;
}