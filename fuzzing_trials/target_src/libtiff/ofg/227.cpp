#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for 'close' and 'mkstemp'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to form a filename and mode
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Prepare mode string
    char mode[3] = {0};
    mode[0] = (char)data[0];
    mode[1] = (char)data[1];
    mode[2] = '\0';

    // Initialize TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (!options) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFF *tiff = TIFFOpenExt(tmpl, mode, options);

    // Clean up
    if (tiff) {
        TIFFClose(tiff);
    }
    TIFFOpenOptionsFree(options);
    remove(tmpl);

    return 0;
}