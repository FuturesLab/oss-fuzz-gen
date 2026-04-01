extern "C" {
    #include <tiffio.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdlib.h> // Include this for mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint32_t tile = TIFFCurrentTile(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}