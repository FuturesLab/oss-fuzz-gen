#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp and close
#include <unistd.h> // For close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_316(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Try different strile indices to call TIFFGetStrileByteCount
    for (uint32_t strileIndex = 0; strileIndex < 10; ++strileIndex) {
        uint64_t byteCount = TIFFGetStrileByteCount(tiff, strileIndex);
        // Use byteCount in some way to avoid compiler optimizations removing the call
        (void)byteCount;
    }

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}