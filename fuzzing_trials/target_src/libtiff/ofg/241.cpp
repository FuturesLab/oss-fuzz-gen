#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_241(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) * 2) {
        return 0; // Not enough data to extract width and height
    }

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file descriptor as FILE*
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open the TIFF file
    }

    // Extract width and height from the data
    uint32_t width = *(reinterpret_cast<const uint32_t*>(data));
    uint32_t height = *(reinterpret_cast<const uint32_t*>(data + sizeof(uint32_t)));

    // Allocate memory for raster
    uint32_t *raster = (uint32_t *)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (!raster) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0; // Failed to allocate memory for raster
    }

    // Call the function-under-test
    int result = TIFFReadRGBAImageOriented(tiff, width, height, raster, ORIENTATION_TOPLEFT, 0);

    // Clean up
    _TIFFfree(raster);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}