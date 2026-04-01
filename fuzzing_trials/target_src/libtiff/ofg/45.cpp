#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h>
#include <cstring>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size < sizeof(toff_t)) {
        return 0; // Not enough data to extract a toff_t value
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create a temporary file
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Unable to open the file descriptor as a FILE*
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        remove(tmpl); // Clean up the temporary file
        return 0; // Unable to open the TIFF file
    }

    // Extract a toff_t value from the data
    toff_t offset;
    memcpy(&offset, data, sizeof(toff_t));

    // Call the function-under-test
    TIFFSetWriteOffset(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}