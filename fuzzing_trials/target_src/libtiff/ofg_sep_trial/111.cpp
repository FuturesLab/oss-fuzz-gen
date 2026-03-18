#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close() and write()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file.
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file.
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF image.
    TIFF* tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare a uint32_t tag value for testing.
    uint32_t tag = 0;
    if (size >= sizeof(uint32_t)) {
        memcpy(&tag, data, sizeof(uint32_t));
    }

    // Call the function-under-test.
    TIFFUnsetField(tiff, tag);

    // Clean up.
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}