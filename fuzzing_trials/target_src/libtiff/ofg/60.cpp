extern "C" {
    #include <tiffio.h>
    #include <unistd.h>  // For close, unlink, and write
    #include <fcntl.h>   // For mkstemp
    #include <sys/types.h> // For ssize_t
    #include <sys/stat.h>  // For mode constants
    #include <stdlib.h> // For mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        int result = TIFFIsUpSampled(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}