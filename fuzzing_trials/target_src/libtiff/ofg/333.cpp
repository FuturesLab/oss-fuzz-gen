#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib> // Include this header for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
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
    close(fd);

    // Open the TIFF file using the TIFFOpen function
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        uint64_t stripSize = TIFFStripSize64(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}