#include <cstdint>
#include <cstdio>
#include <cstdlib> // For mkstemp and remove
#include <unistd.h> // For close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create a temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0; // Unable to open file stream
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Unable to open TIFF
    }

    // Call the function-under-test
    TIFFReadWriteProc writeProc = TIFFGetWriteProc(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}