extern "C" {
    #include <tiffio.h>
    #include <unistd.h> // Include for the 'close' function
    #include <stdlib.h> // Include for 'mkstemp' and 'remove'
    #include <stdio.h>  // Include for 'fdopen', 'fwrite', 'fclose'
    #include <stdint.h> // Include for 'uint8_t', 'uint32_t'
}

extern "C" int LLVMFuzzerTestOneInput_308(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (!tif) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBAStripExt
    uint32_t strip = 0;
    uint32_t buffer[1024]; // Example buffer, size should be sufficient for testing
    int stop_on_error = 0;

    // Call the function-under-test
    TIFFReadRGBAStripExt(tif, strip, buffer, stop_on_error);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}