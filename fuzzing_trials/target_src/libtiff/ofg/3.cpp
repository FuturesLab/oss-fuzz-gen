#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close function
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are treated as C
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF image
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Extract a uint32_t value from the input data for the second parameter
    uint32_t param = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    uint64_t result = TIFFVStripSize64(tiff, param);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}