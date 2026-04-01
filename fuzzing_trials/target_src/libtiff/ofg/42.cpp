#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h> // For close and write
#include <cstdio>   // For remove

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there's at least some data

    // Create a temporary file to write the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFSetupStrips(tiff);

    // Close the TIFF file and clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}