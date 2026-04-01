#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test with a non-zero strip index
    uint32_t stripIndex = 1; // Example strip index
    uint64_t stripSize = TIFFRawStripSize64(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}