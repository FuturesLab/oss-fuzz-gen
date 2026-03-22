#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/jpeglib.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    // Ensure tj3Free is declared for freeing unsigned short *
    void tj3Free(void *buffer); 
}

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    if (size == 0) {
        return 0;
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Initialize variables for function call
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        remove(tmpl);
        return 0;
    }

    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Example pixel format
    int pitch = 0; // Pitch will be calculated based on width and pixel format
    int align = 1; // Alignment parameter for tj3LoadImage16

    // Call the function-under-test
    unsigned short *image = tj3LoadImage16(handle, tmpl, &width, align, &height, &pixelFormat);

    // Clean up
    if (image) {
        tj3Free(image); // Use tj3Free to free the unsigned short * buffer
    }
    tjDestroy(handle);
    remove(tmpl); // Delete the temporary file

    return 0;
}