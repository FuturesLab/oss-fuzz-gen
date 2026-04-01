#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
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

    // Initialize necessary variables
    tjhandle handle = tjInitDecompress();
    if (!handle) {
        remove(tmpl);
        return 0;
    }

    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB;
    int flags = 0;

    // Call the function-under-test
    unsigned short *image = tj3LoadImage16(handle, tmpl, &width, 1, &height, &pixelFormat);

    // Clean up
    if (image) {
        tj3Free(image); // Corrected function to free the image
    }
    tjDestroy(handle);
    remove(tmpl);

    return 0;
}