#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <fcntl.h>
}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    TIFF* tiff = nullptr;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor, so TIFFOpen can open it
    close(fd);

    // Open the TIFF file for reading
    tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        tmsize_t scanlineSize = TIFFScanlineSize(tiff);

        // Clean up
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}