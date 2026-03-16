#include <stdint.h>
#include <cstdio>
#include <unistd.h>  // For mkstemp, close, write
#include <fcntl.h>   // For open
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>   // For remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    TIFF *tiff;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    // Write the fuzz data to the temporary file
    if (fd != -1) {
        write(fd, data, size);
        close(fd);

        // Open the TIFF file
        tiff = TIFFOpen(tmpl, "r");
        if (tiff != NULL) {
            // Call the function-under-test
            uint64_t scanlineSize = TIFFScanlineSize64(tiff);

            // For demonstration purposes, print the scanline size
            printf("Scanline Size: %lu\n", (unsigned long)scanlineSize);

            // Close the TIFF file
            TIFFClose(tiff);
        }

        // Remove the temporary file
        remove(tmpl);
    }

    return 0;
}