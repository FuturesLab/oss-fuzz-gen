#include <cstdint>
#include <cstdio>
#include <unistd.h>  // For close, write, and mkstemp
#include <cstdlib>   // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data to
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
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        // Remove the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function under test
    uint64_t scanlineSize = TIFFRasterScanlineSize64(tif);

    // Clean up
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}