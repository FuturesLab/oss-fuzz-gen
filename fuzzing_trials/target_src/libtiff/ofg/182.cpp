#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Create a temporary file to act as a TIFF image.
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file.
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file.
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test.
    uint64_t rowSize = TIFFTileRowSize64(tiff);

    // Clean up.
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}