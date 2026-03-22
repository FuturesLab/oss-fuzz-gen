#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Initialize the decompressor handle
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        return 0; // If initialization fails, return early
    }

    // Ensure the data size is non-zero to avoid passing a NULL pointer
    if (size == 0) {
        tjDestroy(handle);
        return 0;
    }

    // Allocate memory for width and height
    int width = 0;
    int height = 0;

    // Call the function-under-test
    tjDecompressHeader(handle, (unsigned char *)data, (unsigned long)size, &width, &height);

    // Clean up the decompressor handle
    tjDestroy(handle);

    return 0;
}