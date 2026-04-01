#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // For close
#include <cstring>  // For memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a tag
    }

    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF image
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Extract a tag from the input data
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithTag(tiff, tag);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}