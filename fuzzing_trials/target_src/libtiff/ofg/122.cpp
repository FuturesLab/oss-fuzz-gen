#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close()
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>  // Ensure TIFF library functions are treated as C
}

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
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

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare the tag and value to pass to TIFFGetFieldDefaulted
    uint32_t tag = 0;  // Using 0 as a placeholder, can be adjusted for specific tags
    void *value = malloc(256);  // Allocate some memory for the value

    if (value) {
        // Call the function-under-test
        TIFFGetFieldDefaulted(tiff, tag, value);

        // Free the allocated memory
        free(value);
    }

    // Close the TIFF file and remove the temporary file
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}