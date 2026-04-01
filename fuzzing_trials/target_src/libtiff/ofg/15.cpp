#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Ensure there's enough data for the uint32_t parameter
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file descriptor as FILE*
    }

    // Write the data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Read the uint32_t parameter from the data
    uint32_t stripIndex;
    memcpy(&stripIndex, data, sizeof(uint32_t));

    // Call the function-under-test
    uint64_t result = TIFFRawStripSize64(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}