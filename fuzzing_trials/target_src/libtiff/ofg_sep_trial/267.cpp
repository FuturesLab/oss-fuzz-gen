#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_267(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        int result = TIFFIsBigEndian(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}