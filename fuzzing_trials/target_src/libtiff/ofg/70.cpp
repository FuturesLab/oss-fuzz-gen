#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close() and write()
#include <sys/types.h> // Include for ssize_t
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
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
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare the parameters for TIFFReadRawTile
    uint32_t tile = 0;
    tmsize_t bufsize = 1024;
    void *buf = malloc(bufsize);
    if (buf == nullptr) {
        TIFFClose(tif);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRawTile(tif, tile, buf, bufsize);

    // Cleanup
    free(buf);
    TIFFClose(tif);
    remove(tmpl);

    return 0;
}