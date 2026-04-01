#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close() and write()
#include <sys/types.h>  // Include for ssize_t

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_338(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data to
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF image
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        int result = TIFFIsTiled(tif);

        // Clean up
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}