#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to be a valid JPEG
    }

    tjhandle handle = tjInitDecompress();
    if (handle == NULL) {
        return 0; // Initialization failed
    }

    int width, height, jpegSubsamp, jpegColorspace;
    // Cast away constness for the tjDecompressHeader2 function call
    if (tjDecompressHeader2(handle, const_cast<unsigned char*>(data), size, &width, &height, &jpegSubsamp) == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);
        if (buffer != NULL) {
            // Attempt to decompress the image
            tjDecompress2(handle, const_cast<unsigned char*>(data), size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }

    tjDestroy(handle);
    return 0;
}