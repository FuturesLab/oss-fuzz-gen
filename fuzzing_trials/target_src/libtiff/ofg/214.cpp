#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close() and write()
#include <fcntl.h>  // Include for mkstemp()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
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

    // Close the file descriptor so TIFFOpen can open it
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    const char *filename = TIFFFileName(tiff);

    // Use the filename for some operation to ensure it's not optimized away
    if (filename) {
        printf("TIFF file name: %s\n", filename);
    }

    // Close the TIFF file and remove the temporary file
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}