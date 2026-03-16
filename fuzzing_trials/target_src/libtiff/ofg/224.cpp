#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // For close() and write()
#include <cstdio>    // For remove()
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzz_tiff_XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFFlushData(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}