#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // Include for mkstemp and close
#include <stdlib.h> // Include for remove

extern "C" {
    // Wrap C headers and functions in extern "C" to ensure proper linkage
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    int mode = 0;

    // Ensure the size is sufficient for testing
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary file to simulate a TIFF file
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

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Extract the mode from the data
    mode = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    TIFFSetMode(tiff, mode);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}