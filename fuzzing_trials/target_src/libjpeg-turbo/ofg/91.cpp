#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Exit if handle creation failed
    }

    // Assuming 'data' contains compressed JPEG data, attempt to decompress it
    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = new unsigned char[width * height * tjPixelSize[TJPF_RGB]];

        // Decompress the image
        tjDecompress2(handle, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);

        // Clean up buffer
        delete[] buffer;
    }

    // Clean up
    tjDestroy(handle);

    return 0;
}