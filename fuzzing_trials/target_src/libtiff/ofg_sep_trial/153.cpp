#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a tag
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    ssize_t written = write(fd, data, size);
    if (written != static_cast<ssize_t>(size)) {
        close(fd);
        remove(tmpl);
        return 0; // Failed to write all data
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Extract a uint32_t tag from the data
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithTag(tiff, tag);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}