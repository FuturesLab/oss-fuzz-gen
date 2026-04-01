extern "C" {
    #include <tiffio.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>  // For close() and unlink()
}

extern "C" int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        unlink(tmpl);
        return 0;
    }

    // Read a uint32_t value from the data
    uint32_t strip = 0;
    if (size >= sizeof(uint32_t)) {
        strip = *((uint32_t *)(data + size - sizeof(uint32_t)));
    }

    // Call the function-under-test
    tmsize_t result = TIFFVStripSize(tiff, strip);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}