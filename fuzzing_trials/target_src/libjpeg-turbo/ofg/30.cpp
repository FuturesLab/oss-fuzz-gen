#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close() and unlink()
#include <fcntl.h>  // For mkstemp()
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"

    unsigned short* tj3LoadImage16(tjhandle handle, const char* filename, int* width, int align, int* height, int* pixelFormat);
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl); // Remove the temporary file
        return 0;
    }
    close(fd);

    // Initialize parameters
    tjhandle handle = tjInitDecompress();
    if (handle == nullptr) {
        unlink(tmpl); // Remove the temporary file
        return 0;
    }

    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB; // Assuming RGB as a default pixel format
    int align = 4; // Typical alignment value

    // Call the function-under-test
    unsigned short* image = tj3LoadImage16(handle, tmpl, &width, align, &height, &pixelFormat);

    // Clean up
    if (image != nullptr) {
        free(image); // Use free() instead of tjFree() for unsigned short* buffer
    }
    tjDestroy(handle);
    unlink(tmpl); // Remove the temporary file

    return 0;
}