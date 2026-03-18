#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>  // Include for close() and write()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBAStrip
    uint32_t strip = 0;
    uint32_t* raster = (uint32_t*)malloc(TIFFStripSize(tif) * sizeof(uint32_t));
    if (raster == nullptr) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRGBAStrip(tif, strip, raster);

    // Clean up
    free(raster);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}