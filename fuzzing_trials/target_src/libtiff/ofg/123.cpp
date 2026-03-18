#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close() and remove()
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare arguments for TIFFGetFieldDefaulted
    uint32_t tag = 0; // Initialize tag to a default value
    void *value = malloc(1024); // Allocate memory for the value

    // Call the function-under-test
    TIFFGetFieldDefaulted(tiff, tag, value);

    // Clean up
    free(value);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}