#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include <tiffio.h>
    #include <unistd.h>
    #include <stdlib.h> // Include for mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint32_t currentRow = TIFFCurrentRow(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}