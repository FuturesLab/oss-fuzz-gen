#include <cstdint>
#include <cstdio>
#include <unistd.h> // Include for close, write, and mkstemp
#include <cstdlib>  // Include for remove

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are wrapped with extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        uint64_t scanlineSize = TIFFScanlineSize64(tiff);

        // Clean up
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}