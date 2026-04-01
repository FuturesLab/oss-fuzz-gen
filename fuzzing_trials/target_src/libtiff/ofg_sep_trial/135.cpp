#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        int result = TIFFIsByteSwapped(tiff);

        // Clean up
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}