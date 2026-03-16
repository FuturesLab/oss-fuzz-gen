extern "C" {
    #include <tiffio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <unistd.h>  // Include for close() and write()
}

extern "C" int LLVMFuzzerTestOneInput_315(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        return 0;
    }

    // Fuzz the TIFFGetStrileByteCount function
    uint32_t strileIndex = 0;  // Start with the first strile
    TIFFGetStrileByteCount(tiff, strileIndex);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}