#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // Include the necessary header for 'close'

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
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
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFWriteDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}