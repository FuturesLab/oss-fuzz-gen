#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // For close()
#include <cstring>  // For memcpy()

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_350(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to store the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create a temporary file
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Could not open file descriptor as FILE*
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Could not open TIFF file
    }

    // Extract the tag value from the data
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Call TIFFSetField with the tag and a dummy value
    // We use a dummy value of 0 for simplicity
    int result = TIFFSetField(tiff, tag, 0);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}