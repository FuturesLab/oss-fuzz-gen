#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>  // Include for uint8_t
#include <unistd.h> // Include for close()

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Create a temporary file to store the image data
    char tmpl[] = "/tmp/fuzzimageXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Initialize variables for the function call
    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Use a valid pixel format
    int flags = 0; // No flags

    // Call the function-under-test
    unsigned char *imageBuffer = tjLoadImage(tmpl, &width, 1, &height, &pixelFormat, flags);

    // Clean up
    if (imageBuffer != nullptr) {
        tjFree(imageBuffer);
    }
    remove(tmpl);

    return 0;
}