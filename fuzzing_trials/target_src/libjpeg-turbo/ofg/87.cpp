#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0;
    }

    // Allocate memory for a dummy JPEG header
    unsigned char *jpegHeader = (unsigned char *)malloc(size);
    if (jpegHeader == nullptr) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(jpegHeader, data, size);

    unsigned char *iccProfile = nullptr;
    size_t iccProfileSize = 0;

    // Attempt to decompress the JPEG header to trigger code paths
    int width, height, jpegSubsamp, jpegColorspace;
    if (tjDecompressHeader3(handle, jpegHeader, size, &width, &height, &jpegSubsamp, &jpegColorspace) == 0) {
        // Call the function-under-test
        tj3GetICCProfile(handle, &iccProfile, &iccProfileSize);
    }

    // Clean up
    free(jpegHeader);
    if (iccProfile != nullptr) {
        tjFree(iccProfile);
    }
    tjDestroy(handle);

    return 0;
}