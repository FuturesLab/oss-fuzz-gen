#include "cstdint"
#include <cstdio>
#include "cstdlib"
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff) {
        // Call the function-under-test
        TIFFSeekProc seekProc = TIFFGetSeekProc(tiff);

        // We don't actually use seekProc, just ensure it is retrieved
        (void)seekProc;

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}