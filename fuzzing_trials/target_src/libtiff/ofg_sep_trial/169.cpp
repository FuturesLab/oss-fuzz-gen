#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h> // Include for close()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
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

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRawStrip
    uint32_t strip = 0; // Assuming the first strip for simplicity
    tmsize_t bufferSize = 1024; // Arbitrary buffer size
    void *buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRawStrip(tiff, strip, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}