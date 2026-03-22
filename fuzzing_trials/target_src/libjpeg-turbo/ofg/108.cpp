#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    if (size <= 0) {
        return 0; // Not enough data to process
    }

    tjhandle decompressor = tjInitDecompress();
    if (decompressor == NULL) {
        return 0; // Failed to initialize decompressor
    }

    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(decompressor, data, size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(decompressor);
        return 0; // Failed to read JPEG header
    }

    unsigned char *buffer = tjAlloc(width * height * tjPixelSize[TJPF_RGB]);
    if (buffer == NULL) {
        tjDestroy(decompressor);
        return 0; // Failed to allocate buffer
    }

    if (tjDecompress2(decompressor, data, size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT) != 0) {
        tjFree(buffer);
        tjDestroy(decompressor);
        return 0; // Failed to decompress JPEG
    }

    // Successfully decompressed the image, perform additional operations if needed

    tjFree(buffer);
    tjDestroy(decompressor);

    return 0;
}