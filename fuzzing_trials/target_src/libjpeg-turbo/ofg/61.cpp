#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close()

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    unsigned short * tj3LoadImage16(tjhandle handle, const char *filename, int *width, int align, int *height, int *pixelFormat);

    // Correctly declare tjFree for unsigned char *
    void tjFree(unsigned char *buffer);
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Initialize parameters for tj3LoadImage16
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        remove(tmpl);
        return 0;
    }

    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Use a valid pixel format
    int align = 1; // Default alignment

    // Call the function-under-test
    unsigned short *image = tj3LoadImage16(handle, tmpl, &width, align, &height, &pixelFormat);

    // Clean up
    if (image) {
        // Cast image to unsigned char* for tjFree
        tjFree(reinterpret_cast<unsigned char *>(image));
    }
    tjDestroy(handle);
    remove(tmpl);

    return 0;
}