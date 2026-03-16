#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp and close
#include <unistd.h> // For mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Temporary file creation
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFFlushData(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}