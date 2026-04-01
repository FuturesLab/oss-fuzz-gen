#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Initialize TIFFRGBAImage structure
    TIFFRGBAImage img;
    char emsg[1024];

    // Create a temporary TIFF file from input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;
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

    // Initialize the TIFFRGBAImage
    if (!TIFFRGBAImageBegin(&img, tiff, 0, emsg)) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Allocate memory for raster
    uint32_t width = img.width;
    uint32_t height = img.height;
    uint32_t *raster = (uint32_t *)_TIFFmalloc(width * height * sizeof(uint32_t));
    if (!raster) {
        TIFFRGBAImageEnd(&img);
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFRGBAImageGet(&img, raster, width, height);

    // Clean up
    _TIFFfree(raster);
    TIFFRGBAImageEnd(&img);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}