#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this for the close() function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_349(const uint8_t *data, size_t size) {
    // Create a temporary file to work with TIFF functions
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
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

    // Define a tag and a value to set
    uint32_t tag = 256; // Example tag, could be any valid TIFF tag
    uint32_t value = 1; // Example value, modify as needed

    // Call the function-under-test
    TIFFSetField(tiff, tag, value);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}