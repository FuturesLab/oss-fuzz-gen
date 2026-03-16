#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for close, unlink, and write
#include <fcntl.h>   // Include for mkstemp

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
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
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFSetupStrips(tif);

    // Clean up
    TIFFClose(tif);
    unlink(tmpl);

    return 0;
}