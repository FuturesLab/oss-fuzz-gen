#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h> // Include for close, unlink, write
#include <fcntl.h>  // Include for mkstemp

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl); // Ensure the file is removed if writing fails
        return 0; // If writing fails, exit
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file with libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl); // Ensure the file is removed if TIFFOpen fails
        return 0; // If TIFFOpen fails, exit
    }

    // Call the function-under-test
    TIFFDeferStrileArrayWriting(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}