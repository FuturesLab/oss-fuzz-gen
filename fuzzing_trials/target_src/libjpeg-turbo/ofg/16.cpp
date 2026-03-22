#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);

    if (handle == NULL) {
        return 0;
    }

    if (size < 4) { // Ensure there's enough data for a minimal JPEG header
        tj3Destroy(handle);
        return 0;
    }

    // Attempt to decompress the data
    int width, height, jpegSubsamp, jpegColorspace;
    int result = tjDecompressHeader3(handle, data, size, &width, &height, &jpegSubsamp, &jpegColorspace);

    if (result == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = new unsigned char[width * height * tjPixelSize[TJPF_RGB]];

        // Decompress the image
        result = tjDecompress2(handle, data, size, buffer, width, 0 /* pitch */, height, TJPF_RGB, 0);

        // Free the buffer
        delete[] buffer;
    }

    // Clean up
    tj3Destroy(handle);

    return 0;
}