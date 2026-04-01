#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and remove()

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    TIFF *tiff = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    tiff = TIFFOpen(tmpl, "r");
    if (tiff != NULL) {
        TIFFCreateEXIFDirectory(tiff);
        TIFFClose(tiff);
    }

    remove(tmpl);

    return 0;
}