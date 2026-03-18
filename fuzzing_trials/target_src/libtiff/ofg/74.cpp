extern "C" {
    #include <tiffio.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>  // For close and write functions
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
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
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadWriteProc writeProc = TIFFGetWriteProc(tif);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}