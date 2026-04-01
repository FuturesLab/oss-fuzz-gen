#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp
#include <unistd.h> // For close
#include <cstring>  // For memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to form a valid strip index
    }

    // Create a temporary TIFF file to work with
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file stream
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Extract a uint32_t strip index from the input data
    uint32_t stripIndex;
    memcpy(&stripIndex, data, sizeof(uint32_t));

    // Call the function-under-test
    uint64_t result = TIFFRawStripSize64(tiff, stripIndex);

    // Close the TIFF file and remove the temporary file
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}