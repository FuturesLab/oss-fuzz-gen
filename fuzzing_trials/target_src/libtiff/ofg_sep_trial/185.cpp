#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

// Include necessary headers for mkstemp
#include <cstdlib>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) == -1) {
        close(fd);
        unlink(tmpl);
        return 0; // If write fails, clean up and exit
    }

    // Ensure the file descriptor is at the beginning for reading
    lseek(fd, 0, SEEK_SET);

    // Define the mode string
    const char *mode = "r"; // Open in read mode

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpen(fd, tmpl, mode);

    // Clean up
    if (tiff != nullptr) {
        TIFFClose(tiff);
    }
    close(fd);
    unlink(tmpl);

    return 0;
}