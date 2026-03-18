#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>  // For close() and mkstemp()
#include <stdlib.h>  // For mkstemp()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_344(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a toff_t value
    if (size < sizeof(toff_t)) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Use the first few bytes of data as a toff_t value
    toff_t offset = 0;
    if (size >= sizeof(toff_t)) {
        offset = *(const toff_t *)data;
    }

    // Call the function-under-test with a null TIFFFieldArray
    TIFFReadCustomDirectory(tiff, offset, nullptr);

    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}