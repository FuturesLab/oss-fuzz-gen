#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    // Function signature from the project-under-test
    unsigned char * tjLoadImage(const char *, int *, int, int *, int *, int);
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to contain a valid string and integer values
    if (size < 20) {
        return 0;
    }

    // Allocate memory for the filename string
    char filename[256];
    memset(filename, 0, sizeof(filename));
    strncpy(filename, reinterpret_cast<const char*>(data), sizeof(filename) - 1);

    // Initialize integer parameters
    int width = 0;
    int pitch = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // Example flags

    // Call the function-under-test
    unsigned char *imageData = tjLoadImage(filename, &width, pitch, &height, &pixelFormat, flags);

    // Free the allocated image data if not null
    if (imageData != nullptr) {
        tjFree(imageData);
    }

    return 0;
}