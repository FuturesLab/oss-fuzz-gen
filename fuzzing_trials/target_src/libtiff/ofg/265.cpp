#include <tiffio.h>
#include <unistd.h>  // For close, unlink, write, mkstemp
#include <fcntl.h>   // For open, O_RDWR
#include <cstdint>   // For uint8_t
#include <cstdlib>   // For size_t

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit the fuzzing function
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // If writing fails, clean up and exit
    }

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the TIFF file using the temporary file path
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0; // If TIFFOpen fails, clean up and exit
    }

    // Call the function-under-test
    TIFFMapFileProc mapFileProc = TIFFGetMapFileProc(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}