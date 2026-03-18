#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // for close, unlink, write

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Initialize the TIFFOpenOptions structure
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpenExt(fd, tmpl, "r", options);

    // Clean up
    if (tiff != nullptr) {
        TIFFClose(tiff);
    }
    TIFFOpenOptionsFree(options);
    close(fd);
    unlink(tmpl);

    return 0;
}