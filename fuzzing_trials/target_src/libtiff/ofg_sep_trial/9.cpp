#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this header for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    TIFF *tiff;
    tdir_t directoryIndex;

    // Create a temporary file to simulate a TIFF file
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

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Use the first byte of data as directory index
    directoryIndex = (tdir_t)(data[0] % 256);

    // Call the function-under-test
    TIFFSetDirectory(tiff, directoryIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}