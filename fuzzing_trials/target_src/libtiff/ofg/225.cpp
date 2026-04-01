extern "C" {
    #include <tiffio.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h> // Include this for close() and write()
}

extern "C" int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to hold the TIFF data
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (tif == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFFlushData(tif);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}