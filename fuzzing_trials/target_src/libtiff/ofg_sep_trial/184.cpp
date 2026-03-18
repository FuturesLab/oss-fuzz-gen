#include <tiffio.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) == -1) {
        close(fd);
        unlink(tmpl);
        return 0; // Could not write data to file
    }

    // Ensure the file is ready for reading
    lseek(fd, 0, SEEK_SET);

    // Define the mode for opening the TIFF file
    const char *mode = "r";

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