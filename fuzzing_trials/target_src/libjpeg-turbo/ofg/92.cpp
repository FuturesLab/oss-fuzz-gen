#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0;
    }

    // Check if the input data can be used for decompression
    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Allocate buffer for decompression
        unsigned char *buffer = new unsigned char[width * height * tjPixelSize[TJPF_RGB]];
        if (buffer != NULL) {
            // Decompress the image
            tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            delete[] buffer;
        }
    }

    // Clean up the handle
    tjDestroy(handle);

    return 0;
}