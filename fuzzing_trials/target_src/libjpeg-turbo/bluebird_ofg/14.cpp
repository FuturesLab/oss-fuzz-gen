#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "unistd.h" // For mkstemp, close, write, remove

extern "C" {
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Define and initialize all necessary variables
    if (size < 128 * 128 * 3) {
        return 0; // Ensure there is enough data for a 128x128 RGB image
    }

    char tmpl[] = "/tmp/fuzzimageXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // If writing fails, exit early
    }
    close(fd);

    // Initialize parameters for tjSaveImage
    unsigned char *imageBuffer = const_cast<unsigned char *>(data);
    int width = 128;  // Example width
    int height = 128; // Example height
    int pitch = width * 3; // Assuming 3 bytes per pixel for RGB
    int pixelFormat = TJPF_RGB; // Example pixel format
    int flags = 0; // Example flags

    // Call the function-under-test
    tjSaveImage(tmpl, imageBuffer, width, pitch, height, pixelFormat, flags);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}