#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Call the function-under-test
    tjhandle handle = tjInitDecompress();

    // Check if the handle was successfully created
    if (handle == nullptr) {
        return 0; // If initialization failed, return immediately
    }

    // Check if the input size is sufficient for a minimal JPEG header
    if (size < 2) {
        tjDestroy(handle);
        return 0;
    }

    // Variables to store decompressed image properties
    int width, height, jpegSubsamp;

    // Attempt to read the JPEG header
    int headerResult = tjDecompressHeader2(handle, const_cast<unsigned char*>(data), size, &width, &height, &jpegSubsamp);

    // If the header is valid, proceed with decompression
    if (headerResult == 0) {
        // Allocate buffer for decompressed image
        unsigned char *buffer = (unsigned char *)malloc(width * height * tjPixelSize[TJPF_RGB]);

        // Decompress the JPEG image
        if (buffer != nullptr) {
            tjDecompress2(handle, const_cast<unsigned char*>(data), size, buffer, width, 0, height, TJPF_RGB, TJFLAG_FASTDCT);
            free(buffer);
        }
    }

    // Clean up and free the decompression handle
    tjDestroy(handle);

    return 0;
}