#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
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

    // Close the file descriptor so TIFF can open it
    close(fd);

    // Open the temporary file with TIFF library
    tiff = TIFFOpen(tmpl, "r+");
    if (tiff) {
        // Call the function-under-test
        TIFFWriteDirectory(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}