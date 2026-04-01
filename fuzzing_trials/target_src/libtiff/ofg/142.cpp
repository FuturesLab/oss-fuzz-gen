#include <tiffio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // Include for write() and close()
#include <fcntl.h>    // Include for mkstemp()

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Create a temporary file to write the TIFF data
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

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (tif == NULL) {
        return 0;
    }

    // Call the function-under-test
    TIFFWriteDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}