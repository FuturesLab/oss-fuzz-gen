#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>  // For close and write functions

extern "C" int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file using the temporary file path
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        int result = TIFFIsBigEndian(tiff);
        
        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}