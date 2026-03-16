#include "cstdint"
#include <cstdio>
#include "cstdlib" // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
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
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        tdir_t dir = TIFFCurrentDirectory(tiff);

        // Close the TIFF image
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}