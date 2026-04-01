#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
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

    // Open the TIFF file using the libtiff library
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        uint64_t dirOffset = TIFFCurrentDirOffset(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}