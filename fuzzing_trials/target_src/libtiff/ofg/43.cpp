#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // For close, unlink, and write
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFSetupStrips(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}