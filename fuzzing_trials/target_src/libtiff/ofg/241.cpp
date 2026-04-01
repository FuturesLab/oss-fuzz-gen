#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Not enough data to create a valid TIFF structure
    }

    // Create a temporary file to write the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file stream
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Failed to open TIFF
    }

    // Call the function under test
    int isBigTIFF = TIFFIsBigTIFF(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}