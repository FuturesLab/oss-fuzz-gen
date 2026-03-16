#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close and write functions
#include <sys/types.h>  // Include for ssize_t

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        uint32_t numStrips = TIFFNumberOfStrips(tif);

        // Clean up
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}