extern "C" {
#include <tiffio.h>
#include <unistd.h>  // For close, write, and mkstemp
#include <cstdio>    // For remove
#include <fcntl.h>   // For open, O_RDWR
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>   // For mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_339(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        // If the file could not be opened as a TIFF, clean up and exit
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    int isTiled = TIFFIsTiled(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}