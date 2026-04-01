#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract a valid offset
    if (size < sizeof(toff_t)) {
        return 0;
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tif";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write some data to the file to make it a valid TIFF file
    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        fclose(file);
        remove(tmpl);
        return 0;
    }

    // Extract a toff_t value from the data
    toff_t offset;
    memcpy(&offset, data, sizeof(toff_t));

    // Call the function-under-test
    TIFFSetWriteOffset(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}