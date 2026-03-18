#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close()

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, return early
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF image
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (tif != nullptr) {
        // Call the function under test
        TIFFCheckpointDirectory(tif);
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}