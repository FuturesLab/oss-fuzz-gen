#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// Include the necessary headers for mkstemp
#include <cstdlib>

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t strip = 0;

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor for TIFFOpen to work
    close(fd);

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    tmsize_t result = TIFFRawStripSize(tiff, strip);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}