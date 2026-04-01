#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

extern "C" {
    #include "/src/libjpeg-turbo.3.0.x/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
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

    // Initialize variables
    tjhandle handle = tjInitDecompress();
    int width = 0;
    int height = 0;
    int pixelFormat = TJPF_RGB;
    
    // Call the function-under-test
    int flags = 0; // Assuming no flags for simplicity
    unsigned char *image = tjLoadImage(tmpl, &width, 1, &height, &pixelFormat, flags);

    // Clean up
    tjDestroy(handle);
    if (image) {
        tjFree(image);
    }
    remove(tmpl);

    return 0;
}