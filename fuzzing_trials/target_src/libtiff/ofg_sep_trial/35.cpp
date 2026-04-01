extern "C" {
    #include <tiffio.h>
    #include <unistd.h>  // For close, unlink, and write
    #include <fcntl.h>   // For mkstemp
    #include <stdlib.h>  // For mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If unable to create a temp file, return
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0; // If unable to write all data, return
    }

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the TIFF file using the temporary filename
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        // Call the function-under-test
        TIFFCleanup(tiff);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}