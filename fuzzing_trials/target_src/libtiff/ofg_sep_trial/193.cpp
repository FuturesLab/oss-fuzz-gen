#include <tiffio.h>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
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

    // Open the TIFF file using the temporary file path
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        TIFFCloseProc closeProc = TIFFGetCloseProc(tiff);

        // Ensure the TIFF is closed after use
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}