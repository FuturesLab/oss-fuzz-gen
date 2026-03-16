#include <stdint.h>
#include <stddef.h>
#include <stdio.h>    // For remove
#include <unistd.h>   // For close, write
#include <fcntl.h>    // For mkstemp
#include <cstdlib>    // For mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadWriteProc readProc = TIFFGetReadProc(tiff);
    if (readProc) {
        // Example of using the readProc, assuming it needs a buffer and size
        // This is just a placeholder to demonstrate usage
        char buffer[1024];
        readProc((thandle_t)tiff, buffer, sizeof(buffer));
    }

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}