#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close() and unlink()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a filename
    if (size < 1) {
        return 0;
    }

    // Create a temporary filename
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Open a TIFF file in memory
    TIFF *tiff = TIFFOpen(tmpl, "w");
    if (tiff == NULL) {
        unlink(tmpl); // Clean up temporary file
        return 0;
    }

    // Allocate memory for a filename from the input data
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        TIFFClose(tiff);
        unlink(tmpl); // Clean up temporary file
        return 0;
    }

    // Copy data to filename and ensure null termination
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    const char *result = TIFFSetFileName(tiff, filename);

    // Clean up
    free(filename);
    TIFFClose(tiff);
    unlink(tmpl); // Clean up temporary file

    return 0;
}