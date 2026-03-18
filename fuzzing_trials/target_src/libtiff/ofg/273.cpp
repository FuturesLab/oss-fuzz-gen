#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and write()
#include <fcntl.h>   // Include for mkstemp()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    TIFF *tif = NULL;
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
    tif = TIFFOpen(tmpl, "r");
    if (tif == NULL) {
        return 0;
    }

    // Prepare parameters for TIFFReadEncodedStrip
    uint32_t strip = 0; // Assuming the first strip
    tmsize_t bufsize = TIFFStripSize(tif);
    void *buf = malloc(bufsize);
    if (buf == NULL) {
        TIFFClose(tif);
        return 0;
    }

    // Call the function-under-test
    tmsize_t result = TIFFReadEncodedStrip(tif, strip, buf, bufsize);

    // Clean up
    free(buf);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}