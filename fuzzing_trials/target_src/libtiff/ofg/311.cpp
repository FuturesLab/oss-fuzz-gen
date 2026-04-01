#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close() and write()
#include <fcntl.h>   // Include for mkstemp()

extern "C" int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    TIFF *tiff;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        // Call the function-under-test
        TIFFSizeProc sizeProc = TIFFGetSizeProc(tiff);

        // Use the sizeProc if needed (for example, calling it to get size)
        if (sizeProc != NULL) {
            sizeProc((thandle_t)tiff);
        }

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}