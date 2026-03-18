#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close and unlink

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
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

    // Open the TIFF file using the temporary filename
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        tmsize_t tileSize = TIFFTileSize(tif);
        
        // Print the tile size for debugging purposes
        printf("Tile Size: %ld\n", (long)tileSize);
        
        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}