#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close() and write() functions
#include <fcntl.h>   // Include for mkstemp() function

extern "C" int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        return 0;
    }

    // Use a non-null thandle_t value for testing
    thandle_t clientData = (thandle_t)0x12345678;

    // Call the function-under-test
    TIFFSetClientdata(tif, clientData);

    // Cleanup
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}