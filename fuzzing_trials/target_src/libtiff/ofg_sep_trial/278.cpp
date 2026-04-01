#include <cstdint>
#include <cstdio>
#include <unistd.h>  // Include for close, write, and mkstemp
#include <fcntl.h>   // Include for open
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>   // Include for remove

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_278(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        tdir_t numDirectories = TIFFNumberOfDirectories(tiff);

        // Print the number of directories (optional, for debugging purposes)
        printf("Number of Directories: %u\n", numDirectories);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}