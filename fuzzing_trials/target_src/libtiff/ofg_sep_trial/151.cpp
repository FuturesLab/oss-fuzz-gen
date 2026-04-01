#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function under test
    TIFFCreateEXIFDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}