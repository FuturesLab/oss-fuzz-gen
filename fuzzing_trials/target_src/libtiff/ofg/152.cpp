extern "C" {
    #include <tiffio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h> // for mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Ensure the file descriptor is at the start
    lseek(fd, 0, SEEK_SET);

    // Non-NULL strings for mode and name
    const char *mode = "r";
    const char *name = "fuzzed_tiff";

    // Initialize TIFFOpenOptions
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();
    if (options == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpenExt(fd, name, mode, options);

    // Cleanup
    if (tiff != NULL) {
        TIFFClose(tiff);
    }
    TIFFOpenOptionsFree(options);
    close(fd);
    unlink(tmpl);

    return 0;
}