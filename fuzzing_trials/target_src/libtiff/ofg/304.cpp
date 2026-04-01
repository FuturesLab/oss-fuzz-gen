#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) + sizeof(int)) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tif";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file stream
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open TIFF file
    }

    // Extract a uint32_t and an int from the input data
    uint32_t strile = *(reinterpret_cast<const uint32_t*>(data));
    int error = 0;

    // Call the function-under-test
    uint64_t byteCount = TIFFGetStrileByteCountWithErr(tiff, strile, &error);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}