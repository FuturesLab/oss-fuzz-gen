#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBAStripExt
    uint32_t strip = 0;
    uint32_t buffer[256]; // Example buffer size, can be adjusted
    int stopOnError = 1;  // Example flag value

    // Call the function-under-test
    TIFFReadRGBAStripExt(tiff, strip, buffer, stopOnError);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}