#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for 'close'
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a uint32_t for strile index
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

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Extract a uint32_t from the data for the strile index
    uint32_t strileIndex = *(reinterpret_cast<const uint32_t*>(data));

    // Initialize the error pointer
    int error = 0;

    // Call the function-under-test
    uint64_t byteCount = TIFFGetStrileByteCountWithErr(tiff, strileIndex, &error);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}