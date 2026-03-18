#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a valid path
    if (size < 1) return 0;

    // Allocate memory for the path, ensuring null-termination
    char *path = (char *)malloc(size + 1);
    if (!path) return 0;
    memcpy(path, data, size);
    path[size] = '\0';

    // Initialize parameters for the function call
    tjhandle handle = tjInitDecompress();
    int width = 0;
    int pitch = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB;

    // Call the function-under-test
    unsigned char *image = (unsigned char *)tj3LoadImage16(handle, path, &width, pitch, &height, &pixelFormat);

    // Clean up
    if (image) {
        tjFree(image);
    }
    tjDestroy(handle);
    free(path);

    return 0;
}