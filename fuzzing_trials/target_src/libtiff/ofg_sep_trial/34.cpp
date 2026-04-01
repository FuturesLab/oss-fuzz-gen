#include <cstddef>
#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>  // Include for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the data
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadWriteProc readProc = TIFFGetReadProc(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}